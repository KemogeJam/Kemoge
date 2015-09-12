#include "CM_Img_Player.h"

CM_Img_Player::CM_Img_Player()
	: GameTask({ BIND(CM_Img_Player::Update) }, (int)EPriority::CM_Img_Player)
{
	m_Image = new CharacterImage();
}

void CM_Img_Player::Update()
{

}