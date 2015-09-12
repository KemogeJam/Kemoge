#pragma once
#include "Include.h"

#include "CM_Img_Block.h"

//�}�b�v�̎����������s��
class CM_Sys_MapGenerator : public GameTask
{
private:
	int									m_Level;		//�}�b�v�̓�Փx�@�P�q���̃u���b�N�ʂ����߂�
	int									m_Group;
	GameTaskPointerList<CM_Img_Block>	m_Img_Block;	//�u���b�N�f�[�^

	std::vector<CVector2D>				m_AddList;		//�ǉ��ςݍ��W���X�g

	CFont m_Debug{ L"���C���I", 50 };

private:
	bool PositionCollision(CVector2D target);

	void CreateBlock(CVector2D start, const int back = -1);
	void CrashBlock(int group);

public:
	CM_Sys_MapGenerator(const int level, const int depth);

protected:
	void Update();
};