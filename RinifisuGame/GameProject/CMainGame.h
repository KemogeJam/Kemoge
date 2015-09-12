#pragma once

//�l�X�ȋ@�\
#include "Include.h"

//���̑�
#include "CM_Img_Test.h"

#include "CM_Sys_MapGenerator.h"
#include "CM_Img_GameMap.h"
#include "CM_Img_Number.h"
#include "CM_View_State.h"
#include "CM_Img_Player.h"
#include "CM_ParameterSystem.h"

enum class EGameScene
{
	Create, //����
	Wait,	//�ҋ@

	NewAsset,
	ShowPlayer,
	ShowPlayerWait,

	CountDown,
	CountDownWait,

	GameStart,
	MainGame,


};

class CMainGame : public CScene
{
private:
	EGameScene m_Scene;		//�V�[���̊Ǘ�

private:
	//GameTaskPointer<CM_Sys_MapGenerator> m_Sys_Map;
	GameTaskPointer<CM_Img_Number> m_Img_Num;
	GameTaskPointer<CM_View_State> m_View_State;
	GameTaskPointer<CM_Img_Player>			m_Img_Player;
	CM_ParameterSystem						m_Sys_Parameter;

public:
	CMainGame();
	~CMainGame();

	ESceneChange Update();	//�V�[�����Q�Ƃ��Ċe�N���X�ɖ��߂�^����
};