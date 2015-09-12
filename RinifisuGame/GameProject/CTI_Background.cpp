#include "CTI_Background.h"

CTI_Background::CTI_Background()
	: GameTask({ BIND(CTI_Background::Update) }, 0, 0)
	, m_Image(CGlobal::Get_Image("Test"))
{

}

void CTI_Background::Update()
{
}

void CTI_Background::Draw()
{
	m_Image.Draw();
	m_Image.getPos().x = 100;
	m_Image.getPos().y = 100;
	m_Font.Draw(10, 700, 0.0f, 0.0f, 0.0f, "ƒeƒXƒg");
}
