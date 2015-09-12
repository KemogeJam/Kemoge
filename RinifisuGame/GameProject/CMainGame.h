#pragma once

//様々な機能
#include "Include.h"

//その他
#include "CM_Img_Test.h"

#include "CM_Sys_MapGenerator.h"
#include "CM_Img_Number.h"

enum class EGameScene
{
	Create, //生成
	Wait,	//待機
};

class CMainGame : public CScene
{
private:
	EGameScene m_Scene;		//シーンの管理

private:
	GameTaskPointer<CM_Sys_MapGenerator> m_Sys_Map;
	GameTaskPointer<CM_Img_Number> m_Img_Num;

public:
	CMainGame();
	~CMainGame();

	ESceneChange Update();	//シーンを参照して各クラスに命令を与える
};