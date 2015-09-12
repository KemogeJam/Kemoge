#include "CResult.h"

CResult::CResult()
	: m_Scene(EResultScene::Create)
{
	//�A�Z�b�g�̏�����
	CGlobal::Load_Image("Result\\background");
}

CResult::~CResult()
{

}

ESceneChange CResult::Update()
{
	//�V�[���ŕ���
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

	//�X�y�[�X�L�[�������ƃV�[���ړ�����
	if (CInput::GetState(0, CInput::ePush, CInput::eButton1)) {
		return ESceneChange::Title;
	}

	//����I��
	return ESceneChange::None;
}