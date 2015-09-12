#pragma once
#include "Include.h"

#include "SM_Sys_MapData.h"

//マップの自動生成を行う
class CM_Img_GameMap : public GameTask
{
private:
	SM_Sys_MapData m_Map;

	CFont m_Debug{ L"メイリオ", 50 };

public:
	CM_Img_GameMap(const SM_Sys_MapData & map);

	void CrashBlock(int group);

protected:
	void Update();
};