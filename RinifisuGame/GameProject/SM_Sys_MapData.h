#pragma once
#include "Include.h"

#include "CM_Img_Block.h"

struct SM_Sys_MapData
{
	int									m_Level;		//マップの難易度　１繋ぎのブロック量を決める
	int									m_Group;
	GameTaskPointerList<CM_Img_Block>	m_Img_Block;	//ブロックデータ

	std::vector<CVector2D>				m_AddList;		//追加済み座標リスト
};