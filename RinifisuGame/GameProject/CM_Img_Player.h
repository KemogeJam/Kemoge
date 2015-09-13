#pragma once
#include "Include.h"

#include "CharacterImage.h"

//マップの自動生成を行う
class CM_Img_Player : public GameTask
{
private:
	GameTaskPointer<CharacterImage> m_Player;

public:
	CM_Img_Player();

protected:
	void Update();
};