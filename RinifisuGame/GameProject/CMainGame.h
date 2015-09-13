#pragma once

//様々な機能
#include "Include.h"

//その他
#include "CM_Img_Test.h"

#include "CM_Sys_MapGenerator.h"
#include "CM_Img_Number.h"
#include "CM_View_State.h"
#include "CM_Img_Player.h"
#include "CM_ParameterSystem.h"
#include "CM_Background.h"

enum class EGameScene
{
	Create, //生成
	Wait,	//待機
	GameOver, //ゲームオーバー
};

class CMainGame : public CScene
{
private:
	EGameScene m_Scene;		//シーンの管理

private:
	GameTaskPointer<CM_Background> m_Background;
	GameTaskPointer<CM_Sys_MapGenerator> m_Sys_Map;
	GameTaskPointer<CM_Img_Number> m_Img_Num;
	GameTaskPointer<CM_View_State> m_View_State;
	GameTaskPointer<CM_Img_Player> m_Img_Player;
	CM_ParameterSystem *m_ParameterSystem;

public:
	CMainGame();
	~CMainGame();

	ESceneChange Update();	//シーンを参照して各クラスに命令を与える
};