#include "CR_Background.h"

CR_Background::CR_Background()
	: GameTask({ BIND(CR_Background::Update) }, 0, 0)
	, m_Image(CGlobal::Get_Image("Test"))
{

}

void CR_Background::Update()
{
}

void CR_Background::Draw()
{
	m_Image.Draw();
	m_Image.getPos().x = 100;
	m_Image.getPos().y = 100;
	m_Font.Draw(10, 700, 0.0f, 0.0f, 0.0f, "ƒŠƒUƒ‹ƒg");
}
