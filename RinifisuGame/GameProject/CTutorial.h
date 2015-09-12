#pragma once

//�l�X�ȋ@�\
#include "Include.h"

//���̑�
#include "CTU_Background.h"

enum class ETutorialScene
{
	Create, //����
	Wait,	//�ҋ@
};

class CTutorial : public CScene
{
private:
	ETutorialScene m_Scene;		//�V�[���̊Ǘ�

private:
	GameTaskPointer<CTU_Background> m_Background;

public:
	CTutorial();
	~CTutorial();

	ESceneChange Update();	//�V�[�����Q�Ƃ��Ċe�N���X�ɖ��߂�^����
};
