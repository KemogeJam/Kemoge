#pragma once
#include "Include.h"

#include "SM_Sys_MapData.h"

//�}�b�v�̎����������s��
class CM_Img_GameMap : public GameTask
{
private:
	SM_Sys_MapData m_Map;

	CFont m_Debug{ L"���C���I", 50 };

public:
	CM_Img_GameMap(const SM_Sys_MapData & map);

	void CrashBlock(int group);

protected:
	void Update();
};