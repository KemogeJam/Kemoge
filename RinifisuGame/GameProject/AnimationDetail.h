#pragma once
#include "Include.h"

//アニメーションを定義するクラスです
struct AnimationDetail {
	CVector2D m_Size;
	std::vector<CVector2D> m_Positions; //アニメーションさせる矩形
	bool m_IsLoop = true; //ループするかどうか
	float m_ComaPerFrame; //１コマあたりにかかる時間
};