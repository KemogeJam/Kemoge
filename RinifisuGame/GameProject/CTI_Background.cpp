#include "CTI_Background.h"

CTI_Background::CTI_Background()
	: GameTask({ BIND(CTI_Background::Update) }, 0, 0)
	, m_Image(CGlobal::Get_Image("Title\\background", "Test"))
{

}

void CTI_Background::Update()
{
}

void CTI_Background::Draw()
{
	m_Image.Draw();
}