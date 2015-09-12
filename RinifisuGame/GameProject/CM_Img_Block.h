#pragma once
#include "Include.h"

class CM_Img_Block : public GameTask
{
private:
	CImage		m_Image;		//�摜�f�[�^

	CVector3D	m_Color;		//�F �f�o�b�O

	CFont		m_Debug{ L"���C���I", 165 };

public:
	int			m_Group;		//�P�q����𒲂ׂ�O���[�v

	int			m_Left;
	int			m_Right;
	int			m_Up;
	int			m_Down;

	// -1 ���T��
	//  0 �[
	//�@1 �ڑ���

public:
	CM_Img_Block(const int group, const CVector2D position, const int item = 0);

protected:
	void Update();
	void Draw();
};