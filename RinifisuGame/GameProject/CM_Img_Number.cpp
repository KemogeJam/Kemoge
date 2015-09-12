#include "CM_Img_Number.h"

CM_Img_Number::CM_Img_Number(CVector2D position, bool rightShift)
	: GameTask({ BIND(CM_Img_Number::Update) }, (int)EPriority::CM_Img_Number, (int)EPriority::CM_Img_Number)
	, m_Image(CGlobal::Get_Image("MainGame", "0")), m_RightShift(rightShift), m_ShiftSpace(CGlobal::Get_Rect("MainGame", "0").w + 5)
{
	m_Image.setPos(position);

	m_RectArray = CGlobal::GetArray_Rect("MainGame", { "0" ,"1" ,"2" ,"3" ,"4" ,"5" ,"6" ,"7" ,"8" ,"9" });
}

void CM_Img_Number::SetNumber(double number, bool easing)
{
	if (easing) m_Easing = EasingManager(m_Easing.Out(), number, EaseType::Quad, 1000.0);
	else m_Easing = EasingManager(number, number, EaseType::Quad, 1000.0);
}

void CM_Img_Number::AddNumber(double number, bool easing)
{
	if (easing) m_Easing = EasingManager(m_Easing.Out(), m_Easing.Out(100) + number, EaseType::Quad, 1000.0);
	else m_Easing = EasingManager(m_Easing.Out(100) + number, m_Easing.Out(100) + number, EaseType::Quad, 1000.0);
}

int CM_Img_Number::GetNumber_Int()
{
	return static_cast<int>(m_Easing.Out(100));
}

double CM_Img_Number::GetNumber_Double()
{
	return m_Easing.Out(100);
}

void CM_Img_Number::Update()
{
	EasingSupporter::Auto({ &m_Easing }, false);
}

void CM_Img_Number::Draw()
{
	//”’l‚ÌŒ…”‚ğæ“¾
	int keta = 0;
	while (std::pow(10, ++keta) <= m_Easing.Out());

	//Œ…‚Ì”‚¾‚¯ƒ‹[ƒv
	for (int i = 0; i < keta; i++)
	{
		//À•W‚Ìİ’è ŠÔŠu‚ğ‹ó‚¯‚é
		if (m_RightShift) m_Image.getPos().x += m_ShiftSpace * i;
		else m_Image.getPos().x += m_ShiftSpace * i - (keta - 1) * m_ShiftSpace;

		//‚PŒ…‚Ì’l‚Ìæ‚èo‚µ
		int number = static_cast<int>(m_Easing.Out() / std::pow(10, keta - i - 1)) % 10;

		//•`‰æ”ÍˆÍ‚Ìİ’è
		m_Image.setRect(m_RectArray[number].x, m_RectArray[number].y, m_RectArray[number].x + m_RectArray[number].w, m_RectArray[number].y + m_RectArray[number].h);
		m_Image.setSize(static_cast<float>(m_RectArray[number].w), static_cast<float>(m_RectArray[number].h));

		//‰æ‘œ‚Ì•`‰æ
		m_Image.Draw();
	}
}
