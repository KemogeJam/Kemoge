#pragma once
#include "Include.h"

#include "SM_Sys_MapData.h"

//マップの自動生成を行う
class CM_Sys_MapGenerator : public GameTask
{
private:
	SM_Sys_MapData m_Map;

	CFont m_Debug{ L"メイリオ", 50 };

private:
	bool PositionCollision(CVector2D target);

	void CreateBlock(CVector2D start, const int back = -1);

public:
	CM_Sys_MapGenerator(const int level, const int depth);

	void CrashBlock(int group);

protected:
	void Update();
};