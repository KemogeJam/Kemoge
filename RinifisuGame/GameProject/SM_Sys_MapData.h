#pragma once
#include "Include.h"

#include "CM_Img_Block.h"

struct SM_Sys_MapData
{
	int									m_Level;		//�}�b�v�̓�Փx�@�P�q���̃u���b�N�ʂ����߂�
	int									m_Group;
	GameTaskPointerList<CM_Img_Block>	m_Img_Block;	//�u���b�N�f�[�^

	std::vector<CVector2D>				m_AddList;		//�ǉ��ςݍ��W���X�g
};