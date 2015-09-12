#pragma once

enum class ESceneChange
{
	None,
	Title,
	Tutorial,
	Main,
	Result
};

class CScene
{
public:
	//���z�֐��ɂ��邱�ƂŁA���N���X�̃f�X�g���N�^���Ă΂��
	virtual ~CScene();

	virtual ESceneChange Update();
};