/*!
 *	@brief		カメラクラス
 *	5個のカメラが存在する。
 *　カレントカメラに設定したビュー行列でモデルが表示される。
 */
#pragma once

#include "CVector.h"
#include "CMatrix.h"
#include "CRect.h"
class CCamera {
private:
	CVector3D m_pos;	//カメラの位置
	CVector3D m_at;		//注視点
	CVector3D m_up;		//Upベクトル
	CVector3D m_dir;	//向き（Frontベクトル）
	CMatrix m_mView;	//カメラ行列
	CMatrix m_mProj;	//射影行列
	float	m_whidth;	//カメラの幅
	float	m_height;	//　〃　　高さ
	static CCamera m_camera[5];
	static CCamera *m_pCurrent;
	CRect	m_screen;
public:

	/*!
		@brief	カメラオブジェクトを取得
		@param	num			[in] 取得するカメラの番号
		@retval	カメラオブジェクトのアドレス
	**/
	static CCamera* getCamera(int num=0);
	
	/*!
		@brief	現在使用しているカメラオブジェクトを取得
		@retval	カレントカメラオブジェクトのアドレス
	**/
	static CCamera* getCurrent();

	/*!
		@brief	使用するカメラに設定
		@param	num			[in] 使用するカメラの番号
		@retval　無し
	**/

	static void setCurrent(int num);
	/*!
		@brief	使用するカメラに設定
		@param	p			[in] 使用するカメラのアドレス
		@retval　無し
	**/
	static void setCurrent(CCamera *p);
	/*!
		@brief	コンストラクタ
		@retval　無し
	**/
	CCamera();
	/*!
		@brief	カメラの幅を取得
		@retval　カメラの幅　
	**/
	float getWhidth();
	/*!
		@brief	カメラの高さを取得
		@retval　カメラの高さ　
	**/
	float getHeight();
	/*!
		@brief	カメラの幅と高さ設定
		@param	w			[in] 幅
		@param	h			[in] 高さ
		@retval　無し　
	**/
	void SetSize(float w,float h);

	/*!
		@brief	注視カメラでビュー行列
		@param	eye			[in] 位置
		@param	at			[in] 注視点
		@param	up			[in] 上ベクトル
		@retval　無し　
	**/
	void LookAt(CVector3D &eye,CVector3D &at,CVector3D &up);

	/*!
		@brief	位置と回転値でビュー行列を設定
		@param	pos			[in] 位置
		@param	rot			[in] 回転値
		@retval　無し　
	**/
	void setTranseRot(CVector3D &pos,CVector3D &rot);
	/*!
		@brief	モデル行列からビュー行列を設定
		@param	mtx			[in] モデル行列
		@retval　無し　
	**/
	void setTranseRot(CMatrix &mtx);

	/*!
		@brief	ビュー行列を直接設定
		@param	m			[in] ビュー行列
		@retval　無し　
	**/
	void setMatrix(CMatrix &m);

	/*!
		@brief	ビュー行列を取得
		@retval　無し　
	**/
	CMatrix getMatrix();

	
	/*!
		@brief	ビュー行列を取得
		@retval　無し　
	**/
	CMatrix getBuilbordMatrix();
	
	/*!
		@brief	カメラの位置を取得
		@retval　カメラの位置
	**/
	CVector3D getPos();

	/*!
		@brief	カメラの向きを取得
		@retval　カメラの向き
	**/
	CVector3D getDir();


	/*!
		@brief	射影行列の設定
		@param	m			[in] 射影行列
	**/
	void setProjectionMatrix(CMatrix &m) {
		m_mProj = m;
	}
	/*!
		@brief	 射影行列を取得
		@retval　射影行列
	**/
	CMatrix getProjectionMatrix() {
		return m_mProj;
	}

	void setScreenRect(CRect r) {
		m_screen = r;
	}
	CRect getScreenRect() {
		return m_screen;
	}
};