/*!
 *	@brief		画像管理クラス
 *	
 */

#pragma once

#include "CRect.h"
#include "CMatrix.h"
#include "CShader.h"
#include "CTexture.h"

class CImage{
private:

	CTexture*	m_pTexture;	//テクスチャー
	CVector2D	m_vPos;		//位置(pixel)
	CVector2D	m_vCenter;	//中心位置(pixel)
	CVector2D	m_vSize;	//サイズ(pixel)
	CRect		srcRect;	//表示元矩形
	float		m_ang;		//回転値
	bool		m_flipH;	//左右反転
	CColorRGBA	m_color;	//色

public:
	CVector2D & getPos() { return m_vPos; }

public:
	CImage();
	~CImage();
	/*!
		@brief	ファイルから画像を読み込む（24bitbmp,png対応）
		@param	path		[in] ファイル名
		@retval	結果:true接触 false非接触
	**/
	bool Load(char* path);
	
	/*!
		@brief	画像を破棄する
		@retval	無し
	**/
	
	void Release();

	/*!
		@brief	表示位置を設定する
		@param	x		[in] 横位置
		@param	y		[in] 縦位置
		@retval	無し
	**/
	void setPos(float x,float y) {
		m_vPos.x = x; m_vPos.y = y;
	}
	void setPos(CVector2D p) {
		m_vPos = p;
	}

	/*!
		@brief	回転の中心位置を設定する
		@param	x		[in] 横位置
		@param	y		[in] 縦位置
		@retval	無し
	**/
	void setCenter(float x,float y) {
		m_vCenter.x = x; m_vCenter.y = y;
	}
	void setCenter(CVector2D p) {
		m_vCenter = p;
	}

	/*!
		@brief	表示サイズを設定する
		@param	w		[in] 幅
		@param	h		[in] 高さ
		@retval	無し
	**/
	void setSize(float w,float h) {
		m_vSize.x = w; m_vSize.y = h;
	}
	void setSize(CVector2D s) {
		m_vSize = s;
	}
	/*!
		@brief	表示元矩形を設定
		@param	left	[in] 左位置
		@param	top		[in] 上位置
		@param	right	[in] 右位置
		@param	bottom	[in] 下位置
		@retval	無し
	**/
	void setRect(int left,int top,int right,int bottom){
		srcRect.m_left = static_cast<float>(left);
		srcRect.m_right = static_cast<float>(right);
		srcRect.m_top = static_cast<float>(top);
		srcRect.m_bottom = static_cast<float>(bottom);
	}

	/*!
		@brief	回転値を設定
		@param	ang		[in] 回転値
		@retval	無し
	**/
	void setAng(float ang){
		m_ang = ang;
	}

	/*!
		@brief	左右反転フラグを設定
		@param	f		[in] true:通常 false:水平反転
		@retval	無し
	**/
	void setFlipH(bool f) {
		m_flipH = f;
	}

	/*!
		@brief	色を設定
		@param	r		[in] 赤成分
		@param	g		[in] 緑成分
		@param	b		[in] 青成分
		@param	a		[in] 不透明度
		@retval	無し
	**/
	void setColor(float r, float g, float b,float a){
		m_color.r = r;
		m_color.g = g;
		m_color.b = b;
		m_color.a = a;
	}
	/*!
		@brief	描画を行う
		@retval	無し
	**/
	void Draw();
};