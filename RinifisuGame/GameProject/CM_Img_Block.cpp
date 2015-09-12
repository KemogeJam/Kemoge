#include "CM_Img_Block.h"

CM_Img_Block::CM_Img_Block(const int group, const CVector2D position, const int item)
	: GameTask({ BIND(CM_Img_Block::Update) }, (int)EPriority::CM_Img_Block, (int)EPriority::CM_Img_Block)

	, m_Image(CGlobal::Get_Image("MainGame", "Test"))
	, m_Up(-1), m_Down(-1), m_Left(-1), m_Right(-1)

	, m_Group(group)
{
	m_Image.setPos(position);

	switch (item)
	{
	case 0: //壊れる地面
	{
		switch (m_Group % 4)
		{
		case 0:
			m_Color = CVector3D(1.0f, 1.0f, 0.0f);
			break;

		case 1:
			m_Color = CVector3D(0.0f, 1.0f, 1.0f);
			break;

		case 2:
			m_Color = CVector3D(1.0f, 0.0f, 1.0f);
			break;

		case 3:
			m_Color = CVector3D(0.0f, 1.0f, 0.0f);
			break;
		}
	}
		break;

	case 1: //ミミズ
		m_Color = CVector3D(1.0f, 0.0f, 0.0f);
		break;

	case 2: //スコアボーナス
		m_Color = CVector3D(0.0f, 0.0f, 1.0f);
		break;
	}
}

void CM_Img_Block::Update()
{

}

void CM_Img_Block::Draw()
{
	m_Debug.Draw(static_cast<int>(m_Image.getPos().x), static_cast<int>(m_Image.getPos().y + CGlobal::m_Camera), m_Color.x, m_Color.y, m_Color.z, "●");

	//m_Image.Draw();
}
