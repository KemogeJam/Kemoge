#pragma once
#include "Include.h"

#include "SM_Sys_MapData.h"

//�}�b�v�̎����������s��
class CM_Sys_MapGenerator : public GameTask
{
private:
	SM_Sys_MapData m_Map;

	CFont m_Debug{ L"���C���I", 50 };

private:
	bool PositionCollision(CVector2D target);

	void CreateBlock(CVector2D start, const int back = -1);

public:
	CM_Sys_MapGenerator(const int level, const int depth);
	
	/*�u���b�N��j�󂷂�
	_* return int �󂵂��u���b�N��
	 */
	int CrashBlock(int group);

	SM_Sys_MapData * GetMapDataPointer() { return &m_Map; }

protected:
	void Update();
};