#include "CMainGame.h"

CMainGame::CMainGame()
	: m_Scene(EGameScene::Create)
{
	//アセットの初期化
	CGlobal::Load_Image("MainGame");
	CGlobal::Load_Image("MainGame\\Character");
	CGlobal::Load_Image("MainGame\\ViewState");
	CGlobal::Load_Image("MainGame\\MainGame_Block");
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
		m_ParameterSystem = new CM_ParameterSystem();
		m_ParameterSystem->Init();

		//m_Img_Num = new CM_Img_Number( );
		m_Img_Player = new CM_Img_Player();

		m_Scene = EGameScene::Wait;
		break;

		//----------------------------------------------------------------------------------------------------------//

	case EGameScene::Wait:
	{
		static int debug = 0;

		m_ParameterSystem->Update();
		m_View_State->UpdateEnergy(m_ParameterSystem->GetEnergy());
		m_View_State->UpdateDepthCount(m_ParameterSystem->GetRemainDepth());
		m_View_State->UpdatePts(m_ParameterSystem->GetScore());
		m_View_State->UpdateLife(m_ParameterSystem->GetLife());

		if (CInput::GetState(0, CInput::ePush, CInput::eButton1))
		{
			int blockCount = m_Sys_Map->CrashBlock(++debug);
			m_ParameterSystem->BreakBlock(blockCount);
		}

		//ゲームオーバー確認
		if (m_ParameterSystem->IsgameOver()) {
			m_Scene = EGameScene::GameOver;
		}
	}
		break;

		//----------------------------------------------------------------------------------------------------------//
	case EGameScene::GameOver:
		if (CInput::GetState(0, CInput::ePush, CInput::eButton1))
		{
			return ESceneChange::Title;
		}
		break;

	default:

		break;
	}

	//正常終了
	return ESceneChange::None;
}