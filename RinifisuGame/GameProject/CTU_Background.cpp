#include "CTU_Background.h"

CTU_Background::CTU_Background()
	: GameTask({ BIND(CTU_Background::Update) }, 0, 0)
	, m_Image(CGlobal::Get_Image("Title\\background", "Test"))
{

}

void CTU_Background::Update()
{
}

void CTU_Background::Draw()
{
	m_Image.Draw();
	m_Font.Draw(10, 700, 0.0f, 0.0f, 0.0f, "チュートリアル");
}
