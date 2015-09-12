#include "CM_Sys_MapGenerator.h"

CM_Sys_MapGenerator::CM_Sys_MapGenerator(const int level, const int depth)
	: GameTask({ BIND(CM_Sys_MapGenerator::Update) }, (int)EPriority::CM_Sys_MapGenerator)

	, m_Map({level, 0})
{
	//深さ分だけ生成する
	for (int l_Depth = 0; l_Depth < depth; ++l_Depth)
	{
		//横幅分だけ生成する
		for (int l_Parallel = 0; l_Parallel < 9; ++l_Parallel)
		{
			//ブロックを生成する
			CreateBlock(CVector2D(static_cast<float>(l_Parallel), static_cast<float>(l_Depth)));
		}
	}
}

bool CM_Sys_MapGenerator::PositionCollision(CVector2D target)
{
	std::vector<CVector2D>::const_iterator it = m_Map.m_AddList.begin();
	std::vector<CVector2D>::const_iterator end_It = m_Map.m_AddList.end();

	while (it != end_It)
	{
		if (static_cast<int>(it->x) == static_cast<int>(target.x)
			&& static_cast<int>(it->y) == static_cast<int>(target.y))
		{
			return true;
		}

		++it;
	}

	return false;
}

void CM_Sys_MapGenerator::CreateBlock(CVector2D start, const int back)
{
	//座標がかぶっていればその場で終了
	if (PositionCollision(start) || start.x < 0.0f || 8.0f < start.x || start.y < 0.0f) return;

	if (back == -1) m_Map.m_Group++;

	unsigned int nextID = m_Map.m_Img_Block.nextID();
	CVector2D createPosition(200.0f + 80.0f * start.x, 200.0f + 80.0f * start.y);
	m_Map.m_Img_Block.Add(new CM_Img_Block(m_Map.m_Group, createPosition));
	m_Map.m_AddList.push_back(start);

	switch (back)
	{
	case 0: //上
		m_Map.m_Img_Block(nextID).m_Down = 1;
		break;

	case 1: //下
		m_Map.m_Img_Block(nextID).m_Up = 1;
		break;

	case 2: //左
		m_Map.m_Img_Block(nextID).m_Right = 1;
		break;

	case 3: //右
		m_Map.m_Img_Block(nextID).m_Left = 1;
		break;
	}

	if (m_Map.m_Img_Block(nextID).m_Up == -1 && std::rand() % 5 == 0)
	{
		CreateBlock(start + CVector2D(0, -1), 0);
		m_Map.m_Img_Block(nextID).m_Up = 1;
	}
	else m_Map.m_Img_Block(nextID).m_Up = 0;

	if (m_Map.m_Img_Block(nextID).m_Down == -1 && std::rand() % 5 == 0)
	{
		CreateBlock(start + CVector2D(0, 1), 1);
		m_Map.m_Img_Block(nextID).m_Down = 1;
	}
	else m_Map.m_Img_Block(nextID).m_Down = 0;

	if (m_Map.m_Img_Block(nextID).m_Left == -1 && std::rand() % 5 == 0)
	{
		CreateBlock(start + CVector2D(-1, 0), 2);
		m_Map.m_Img_Block(nextID).m_Left = 1;
	}
	else m_Map.m_Img_Block(nextID).m_Left = 0;

	if (m_Map.m_Img_Block(nextID).m_Right == -1 && std::rand() % 5 == 0)
	{
		CreateBlock(start + CVector2D(1, 0), 3);
		m_Map.m_Img_Block(nextID).m_Right = 1;
	}
	else m_Map.m_Img_Block(nextID).m_Right = 0;
}

void CM_Sys_MapGenerator::CrashBlock(int group)
{
	for (unsigned int i = 0; i < m_Map.m_Img_Block.size(); i++)
	{
		if (group == m_Map.m_Img_Block[i].m_Group)
		{
			m_Map.m_Img_Block.Clear(i);
			i = -1;
		}
	}
}

void CM_Sys_MapGenerator::Update()
{
	if (CInput::GetState(0, CInput::eHold, CInput::eMouseL))
	CGlobal::m_Camera += CInput::getMouseVec().y;

	m_Debug.Draw(10, 700, 0.0f, 0.0f, 0.0f, const_cast<char*>(std::to_string(CGlobal::m_Camera / 80.0f).c_str()));
}