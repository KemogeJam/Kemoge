#pragma once
#include "Include.h"

#include "CM_Img_Block.h"

#define GETIMAGE m_Img_Block[i].GetImagePointer()

struct SM_Sys_MapData
{
	int									m_Level;		//マップの難易度　１繋ぎのブロック量を決める
	int									m_Group;
	GameTaskPointerList<CM_Img_Block>	m_Img_Block;	//ブロックデータ

	std::vector<CVector2D>				m_AddList;		//追加済み座標リスト

	bool Collision(CImage * target)
	{
		for (int i = 0; i < m_Img_Block.size(); i++)
		{
			float mx1 = target->getPos().x;
			float my1 = target->getPos().y;
			float mx2 = target->getPos().x + target->getSize().x;
			float my2 = target->getPos().y + target->getSize().x;

			float ex1 = GETIMAGE->getPos().x;
			float ey1 = GETIMAGE->getPos().y;
			float ex2 = GETIMAGE->getPos().x + GETIMAGE->getSize().x;
			float ey2 = GETIMAGE->getPos().y + GETIMAGE->getSize().x;

			if (mx1 <= ex2 && ex1 <= mx2 && my1 <= ey2 && ey1 <= my2)
			{
				return true;
			}
		}

		return false;
	}
};