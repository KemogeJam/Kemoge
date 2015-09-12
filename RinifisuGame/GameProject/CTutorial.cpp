#include "CTutorial.h"

CTutorial::CTutorial()
	: m_Scene(ETutorialScene::Create)
{
	//アセットの初期化
	CGlobal::Load_Image("Tutorial\\background");
}

CTutorial::~CTutorial()
{

}

ESceneChange CTutorial::Update()
{
	//シーンで分岐
	switch (m_Scene)
	{
	case ETutorialScene::Create:
		m_Background = new CTU_Background();
		m_Scene = ETutorialScene::Wait;
		break;

		//----------------------------------------------------------------------------------------------------------//

	case ETutorialScene::Wait:

		break;

		//----------------------------------------------------------------------------------------------------------//

	default:

		break;
	}

	//スペースキーを押すとシーン移動する
	if (CInput::GetState(0, CInput::ePush, CInput::eButton1)) {
		return ESceneChange::Main;
	}

	//正常終了
	return ESceneChange::None;
}