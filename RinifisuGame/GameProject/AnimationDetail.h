#pragma once
#include "Include.h"

//�A�j���[�V�������`����N���X�ł�
struct AnimationDetail {
	CVector2D m_Size;
	std::vector<CVector2D> m_Positions; //�A�j���[�V�����������`
	bool m_IsLoop = true; //���[�v���邩�ǂ���
	float m_ComaPerFrame; //�P�R�}������ɂ����鎞��
};