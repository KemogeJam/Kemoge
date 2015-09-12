#include "CM_Img_Test.h"

CM_Img_Test::CM_Img_Test()
	: GameTask({ BIND(CM_Img_Test::Update) }, (int)EPriority::CM_Img_Test, (int)EPriority::CM_Img_Test)
	, m_Image(CGlobal::Get_Image("MainGame", "Test"))
{

}

void CM_Img_Test::Update()
{
	++m_Image.getPos().x;
}

void CM_Img_Test::Draw()
{
	m_Image.Draw();

	m_Font.Draw(10, 700, 0.0f, 0.0f, 0.0f, "ƒeƒXƒg");
}
