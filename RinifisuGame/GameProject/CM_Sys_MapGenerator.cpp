#include "CM_Sys_MapGenerator.h"

CM_Sys_MapGenerator::CM_Sys_MapGenerator(const int level, const int depth) : m_Map({level, 0})
{
	//深さ分だけ生成する
	for (int l_Depth = 0; l_Depth < depth; ++l_Depth)
	{
		//20回に1回の確率でアイテムを出現させる
		if (l_Depth % 20 == 0)
		{
			int randCreatePos = std::rand() % 9;
			unsigned int nextID = m_Map.m_Img_Block.nextID();
			CVector2D createPosition(200.0f + 80.0f * randCreatePos, 200.0f + 80.0f * l_Depth);

			m_Map.m_Img_Block.Add(new CM_Img_Block(++m_Map.m_Group, createPosition, std::rand() % 2));

			m_Map.m_AddList.push_back(CVector2D(randCreatePos, l_Depth));
		}

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
		//位置が同じであればtrue
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

	//グループをずらす
	if (back == -1) m_Map.m_Group++;

	//ブロックの生成
	unsigned int nextID = m_Map.m_Img_Block.nextID();
	CVector2D createPosition(200.0f + 80.0f * start.x, 200.0f + 80.0f * start.y);
	m_Map.m_Img_Block.Add(new CM_Img_Block(m_Map.m_Group, createPosition));
	m_Map.m_AddList.push_back(start);

	//接続部を設定する
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

	//２０％の確率でブロックの周囲にブロックが生成される
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

SM_Sys_MapData CM_Sys_MapGenerator::GetData()
{
	return m_Map;
}
