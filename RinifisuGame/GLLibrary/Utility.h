
#include "GL.h"
#include "CMatrix.h"
#include <cmath>

namespace Utility {
	/*!
		@brief	Degree（度）をRadianに変換
		@param	d				[in] 角度
		@retval	Radianに変換された角度
	**/

	inline float DgreeToRadian(float d) {
		return d*static_cast<float>(M_PI) /180.0f;
	}
	/*!
		@brief	角度の正規化
		@param	a				[in] 角度
		@retval	-PI～PI
	**/

	inline float NormalizeAngle(float a) {
		if(a>static_cast<float>(M_PI)) return a- static_cast<float>(M_PI) * 2.0f;
		else if(a<-static_cast<float>(M_PI)) return a+ static_cast<float>(M_PI) * 2.0f;
		return a;
	}
	/*!
		@brief	角度の差を取得
		@param	a			[in] 角度
		@param	b			[in] 角度
		@retval	aとbの角度の差
	**/

	inline float DiffAngle(float a,float b) {
		if(a*b < 0.0f){
			if(abs(a)+abs(b) > static_cast<float>(M_PI)) {
				if(b<0.0f) a-= static_cast<float>(M_PI) *2.0f;
				else a+= static_cast<float>(M_PI) *2.0f;
			}
		}
		return b-a;
	}
	/*!
		@brief	乱数取得
		@param	min				[in] 最低値
		@param	max				[in] 最大値
		@retval	最低値～最大値の乱数
	**/

	template <typename T> inline T Rand(T min,T max) {
		return min + ((max-min) * rand()/ RAND_MAX);
	}
	/*!
		@brief	スクリーン座標変換→ワールド座標
		@param	out				[out] ワールド座標
		@param	spos			[in] スクリーン座標
		@param	mProj			[in] 射影行列
		@param	mView			[in] ビュー行列
		@param	w				[in] スクリーン幅
		@param	h				[in] スクリーン高さ
		@retval	無し
	**/
	void ScreenToWorld(CVector3D *out,CVector3D spos,CMatrix mProj,CMatrix mView,int w,int h);
	/*!
		@brief	ワールド座標→スクリーン座標変換
		@param	out				[out] スクリーン座標
		@param	wpos			[in] ワールド座標
		@param	mProj			[in] 射影行列
		@param	mView			[in] ビュー行列
		@param	w				[in] スクリーン幅
		@param	h				[in] スクリーン高さ
		@retval	無し
	**/
	void WorldToScreen(CVector3D *out,CVector3D wpos,CMatrix mProj,CMatrix mView,int w,int h);
}