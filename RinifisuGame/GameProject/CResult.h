#pragma once

//�l�X�ȋ@�\
#include "Include.h"

//���̑�
#include "CR_Background.h"

enum class EResultScene
{
	Create, //����
	Wait,	//�ҋ@
};

class CResult : public CScene
{
private:
	EResultScene m_Scene;		//�V�[���̊Ǘ�

private:
	GameTaskPointer<CR_Background> m_Background;

public:
	CResult();
	~CResult();

	ESceneChange Update();	//�V�[�����Q�Ƃ��Ċe�N���X�ɖ��߂�^����
};