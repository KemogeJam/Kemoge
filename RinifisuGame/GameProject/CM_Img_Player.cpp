#include "CM_Img_Player.h"

CM_Img_Player::CM_Img_Player(SM_Sys_MapData * mapPointer)
	: GameTask({ BIND(CM_Img_Player::Update) }, (int)EPriority::CM_Img_Player)
	, m_Jump(0.0f), m_JumpFlag(false), mp_Map(mapPointer)
{
	m_Player = new CharacterImage();
}

void CM_Img_Player::Update()
{
	if (CInput::GetState(0, CInput::eHold, CInput::eLeft))
	{
		m_Player->getImage().getPos().x -= 4;
	}

	else if (CInput::GetState(0, CInput::eHold, CInput::eRight))
	{
		m_Player->getImage().getPos().x += 4;
	}

	if (mp_Map->Collision(&m_Player->getImage()))
	{
		m_Jump = 0.0f;
		m_JumpFlag = false;
	}

	if (CInput::GetState(0, CInput::ePush, CInput::eButton1))
	{
		m_Jump = 8.0f;
		m_JumpFlag = true;
	}
	
	if (m_JumpFlag)
	{
		m_Jump -= 0.2f;
		CGlobal::m_Camera += m_Jump;
	}
}