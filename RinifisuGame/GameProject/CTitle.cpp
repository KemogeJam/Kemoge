#include "CTitle.h"

CTitle::CTitle()
	: m_Scene(ETitleScene::Create)
{
	//�A�Z�b�g�̏�����
	CGlobal::Load_Image("Title\\background");
}

CTitle::~CTitle()
{

}

ESceneChange CTitle::Update()
{
	//�V�[���ŕ���
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

	//�X�y�[�X�L�[�������ƃV�[���ړ�����
	if(CInput::GetState(0, CInput::ePush, CInput::eButton1)) {
		return ESceneChange::Tutorial;
	}

	//����I��
	return ESceneChange::None;
}