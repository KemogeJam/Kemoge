#include "CMainGame.h"

CMainGame::CMainGame()
	: m_Scene(EGameScene::NewAsset)
{
	//アセットの初期化
	CGlobal::Load_Image("MainGame");
	CGlobal::Load_Image("MainGame\\ViewState");
	CGlobal::Load_Image("MainGame\\Character");
}

CMainGame::~CMainGame()
{

}

ESceneChange CMainGame::Update()
{
	//シーンで分岐
	switch (m_Scene)
	{
	case EGameScene::Create:
//		m_Sys_Map = new CM_Sys_MapGenerator(10, 20);
		m_View_State = new CM_View_State();
		//----------------------------------------------------------------------------------------------------------//

	case EGameScene::NewAsset:
	{
		//CM_Sys_MapGenerator generator(1, 100);
		//m_Sys_Map = new CM_Img_GameMap(generator.GetData());
	}

	m_Img_Player = new CM_Img_Player();
		break;

		//----------------------------------------------------------------------------------------------------------//
	case EGameScene::ShowPlayer:

		break;

		//----------------------------------------------------------------------------------------------------------//
	case EGameScene::ShowPlayerWait:

		break;

		//----------------------------------------------------------------------------------------------------------//
	case EGameScene::CountDown:

		break;

		//----------------------------------------------------------------------------------------------------------//
	case EGameScene::CountDownWait:

		break;

		//----------------------------------------------------------------------------------------------------------//
	case EGameScene::GameStart:

		break;

		//----------------------------------------------------------------------------------------------------------//
	case EGameScene::MainGame:

		break;

		//----------------------------------------------------------------------------------------------------------//

	default:

		break;
	}

	//正常終了
	return ESceneChange::None;
}