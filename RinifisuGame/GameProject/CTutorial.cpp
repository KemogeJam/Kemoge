#include "CTutorial.h"

CTutorial::CTutorial()
	: m_Scene(ETutorialScene::Create)
{
	//�A�Z�b�g�̏�����
	CGlobal::Load_Image("Tutorial\\background");
}

CTutorial::~CTutorial()
{

}

ESceneChange CTutorial::Update()
{
	//�V�[���ŕ���
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

	//�X�y�[�X�L�[�������ƃV�[���ړ�����
	if (CInput::GetState(0, CInput::ePush, CInput::eButton1)) {
		return ESceneChange::Main;
	}

	//����I��
	return ESceneChange::None;
}