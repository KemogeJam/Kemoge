#pragma once
#include "Include.h"

#include "SM_Sys_MapData.h"
#include "CharacterImage.h"

//�}�b�v�̎����������s��
class CM_Img_Player : public GameTask
{
private:
	GameTaskPointer<CharacterImage> m_Image;

public:
	CM_Img_Player();

protected:
	void Update();
};