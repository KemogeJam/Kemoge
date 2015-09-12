#pragma once

//�l�X�ȋ@�\
#include "Include.h"

//���̑�
#include "CM_Img_Test.h"

#include "CM_Sys_MapGenerator.h"
#include "CM_Img_Number.h"

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
	GameTaskPointer<CM_Sys_MapGenerator> m_Sys_Map;
	GameTaskPointer<CM_Img_Number> m_Img_Num;

public:
	CMainGame();
	~CMainGame();

	ESceneChange Update();	//�V�[�����Q�Ƃ��Ċe�N���X�ɖ��߂�^����
};