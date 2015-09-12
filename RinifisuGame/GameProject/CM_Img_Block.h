#pragma once
#include "Include.h"

class CM_Img_Block : public GameTask
{
private:
	CImage		m_Image;		//画像データ

	CVector3D	m_Color;		//色 デバッグ

	CFont		m_Debug{ L"メイリオ", 165 };

public:
	int			m_Group;		//１繋がりを調べるグループ

	int			m_Left;
	int			m_Right;
	int			m_Up;
	int			m_Down;

	// -1 未探索
	//  0 端
	//　1 接続部

public:
	CM_Img_Block(const int group, const CVector2D position, const int item = 0);

protected:
	void Update();
	void Draw();
};