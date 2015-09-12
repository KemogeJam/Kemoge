#pragma once

//�l�X�ȋ@�\
#include "Include.h"

//���̑�
#include "CM_Img_Test.h"
#include "CharacterImage.h"

enum class EGameScene
{
	Create, //����
	Wait,	//�ҋ@
};

class CMainGame : public CScene
{
private:
	EGameScene m_Scene;		//�V�[���̊Ǘ�

private:
	GameTaskPointer<CM_Img_Test> m_Img_Text;
	GameTaskPointer<CharacterImage> m_CharacterImage;

public:
	CMainGame();
	~CMainGame();

	ESceneChange Update();	//�V�[�����Q�Ƃ��Ċe�N���X�ɖ��߂�^����
};