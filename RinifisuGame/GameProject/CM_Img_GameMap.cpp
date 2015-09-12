#include "CM_Img_GameMap.h"

CM_Img_GameMap::CM_Img_GameMap(const SM_Sys_MapData & map)
	: GameTask({ BIND(CM_Img_GameMap::Update) }, (int)EPriority::CM_Img_GameMap)

	, m_Map(map)
{

}

void CM_Img_GameMap::CrashBlock(int group)
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

void CM_Img_GameMap::Update()
{
	if (CInput::GetState(0, CInput::eHold, CInput::eMouseL))
		CGlobal::m_Camera += CInput::getMouseVec().y;

	m_Debug.Draw(10, 700, 0.0f, 0.0f, 0.0f, const_cast<char*>(std::to_string(CGlobal::m_Camera / 80.0f).c_str()));
}