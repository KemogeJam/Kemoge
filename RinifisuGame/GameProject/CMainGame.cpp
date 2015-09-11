#include "CMainGame.h"

CMainGame::CMainGame()
	: m_Scene(EGameScene::Create)
{
	//アセットの初期化
	CGlobal::Load_Image("MainGame");
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
		m_Img_Text = new CM_Img_Test();

		m_Scene = EGameScene::Wait;
		break;

		//----------------------------------------------------------------------------------------------------------//

	case EGameScene::Wait:

		break;

		//----------------------------------------------------------------------------------------------------------//

	default:

		break;
	}

	//正常終了
	return ESceneChange::None;
}