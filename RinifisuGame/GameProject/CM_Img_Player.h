#pragma once
#include "Include.h"

#include "CharacterImage.h"
#include "SM_Sys_MapData.h"

//マップの自動生成を行う
class CM_Img_Player : public GameTask
{
private:
	GameTaskPointer<CharacterImage> m_Player;
	float m_Jump;
	bool m_JumpFlag;

	SM_Sys_MapData* mp_Map;

public:
	CM_Img_Player(SM_Sys_MapData * mapPointer);

protected:
	void Update();
};