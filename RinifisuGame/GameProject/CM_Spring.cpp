#include "CM_Spring.h"

CM_Spring::CM_Spring()
	: GameTask({ BIND(CM_Spring::Update) }, 3, 3)
{
	m_ImageSpring = CGlobal::Get_Image("MainGame\\MainGame_Back", "Background");
	m_ImageSpring.setColor(1.0f, 1.0f, 1.0f, 0.35f);
	m_ImageSpring.getPos().x = 80;

}

void CM_Spring::Update()
{
}

void CM_Spring::Draw()
{
	m_ImageSpring.Draw();
}
