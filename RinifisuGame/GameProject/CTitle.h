#pragma once

//�l�X�ȋ@�\
#include "Include.h"

//���̑�
#include "CTI_Background.h"

enum class ETitleScene
{
	Create, //����
	Wait,	//�ҋ@
};

class CTitle : public CScene
{
private:
	ETitleScene m_Scene;		//�V�[���̊Ǘ�

private:
	GameTaskPointer<CTI_Background> m_Background;

public:
	CTitle();
	~CTitle();

	ESceneChange Update();	//�V�[�����Q�Ƃ��Ċe�N���X�ɖ��߂�^����
};
