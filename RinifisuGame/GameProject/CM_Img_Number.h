#pragma once
#include "Include.h"

class CM_Img_Number : public GameTask
{
private:
	CImage						m_Image;		//画像データ
	std::vector<TextureRect>	m_RectArray;	//数値データ

	bool						m_RightShift;	//数値描画時のシフト方向
	float						m_ShiftSpace;	//数値間のスペース

	EasingManager				m_Easing;		//値移動

public:
	CM_Img_Number(CVector2D position, bool rightShift);

	void SetNumber(double number, bool easing);
	void AddNumber(double number, bool easing);

	int GetNumber_Int();
	double GetNumber_Double();

protected:
	void Update();
	void Draw();
};