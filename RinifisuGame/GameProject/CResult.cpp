#include "CResult.h"

CResult::CResult()
	: m_Scene(EResultScene::Create)
{
	//アセットの初期化
	CGlobal::Load_Image("Result\\background");
}

CResult::~CResult()
{

}

ESceneChange CResult::Update()
{
	//シーンで分岐
	switch (m_Scene)
	{
	case EResultScene::Create:
		m_Background = new CR_Background();
		m_Scene = EResultScene::Wait;
		break;

		//----------------------------------------------------------------------------------------------------------//

	case EResultScene::Wait:

		break;

		//----------------------------------------------------------------------------------------------------------//

	default:

		break;
	}

	//スペースキーを押すとシーン移動する
	if (CInput::GetState(0, CInput::ePush, CInput::eButton1)) {
		return ESceneChange::Title;
	}

	//正常終了
	return ESceneChange::None;
}