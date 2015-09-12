#pragma once
#include "Include.h"

#include "SM_Sys_MapData.h"

//マップの自動生成を行う
class CM_Sys_MapGenerator
{
private:
	SM_Sys_MapData m_Map;

private:
	bool PositionCollision(CVector2D target);
	void CreateBlock(CVector2D start, const int back = -1);

public:
	CM_Sys_MapGenerator(const int level, const int depth);

	SM_Sys_MapData GetData();
};