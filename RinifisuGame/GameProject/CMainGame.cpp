#include "CMainGame.h"

CMainGame::CMainGame()
	: m_Scene(EGameScene::Create)
{
	//アセットの初期化
	CGlobal::Load_Image("MainGame");
	CGlobal::Load_Image("MainGame\\ViewState");
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
		m_Sys_Map = new CM_Sys_MapGenerator(10, 20);
		m_View_State = new CM_View_State();

		//m_Img_Num = new CM_Img_Number( );

		m_Scene = EGameScene::Wait;
		break;

		//----------------------------------------------------------------------------------------------------------//

	case EGameScene::Wait:
	{
		static int debug = 0;

		if (CInput::GetState(0, CInput::ePush, CInput::eButton1))
		{
			m_Sys_Map->CrashBlock(++debug);
		}
	}
		break;

		//----------------------------------------------------------------------------------------------------------//

	default:

		break;
	}

	//正常終了
	return ESceneChange::None;
}