#include "CM_Background.h"

CM_Background::CM_Background()
	: GameTask({ BIND(CM_Background::Update) }, 0, 0)
{
	m_ImageBackground = CGlobal::Get_Image("MainGame\\MainGame_Back", "Background");
	m_ImageBackground.getPos().x = 80;

	m_ImageLeft = CGlobal::Get_Image("MainGame\\MainGame_Back", "Side");
	m_ImageRight = CGlobal::Get_Image("MainGame\\MainGame_Back", "Side");
	m_ImageLeft.getPos().x = 800;

}

void CM_Background::Update()
{
}

void CM_Background::Draw()
{
	m_ImageBackground.Draw();
	m_ImageLeft.Draw();
	m_ImageRight.Draw();
}
