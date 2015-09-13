#include "CTitle.h"

CTitle::CTitle()
	: m_Scene(ETitleScene::Create)
{
	//アセットの初期化
	CGlobal::Load_Image("Title\\background");
}

CTitle::~CTitle()
{

}

ESceneChange CTitle::Update()
{
	//シーンで分岐
	switch (m_Scene)
	{
	case ETitleScene::Create:
		m_Background = new CTI_Background();
		m_Scene = ETitleScene::Wait;
		break;

		//----------------------------------------------------------------------------------------------------------//

	case ETitleScene::Wait:

		break;

		//----------------------------------------------------------------------------------------------------------//

	default:

		break;
	}

	//スペースキーを押すとシーン移動する
	if(CInput::GetState(0, CInput::ePush, CInput::eButton1)) {
		return ESceneChange::Tutorial;
	}

	//正常終了
	return ESceneChange::None;
}