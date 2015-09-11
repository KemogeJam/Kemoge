/*!
*	@brief	キー入力クラス
*
*
**/
#pragma once
#include "windows.h"
#include "CVector.h"

#define PAD_MAX 5

class CInput {
public:
	enum E_STATE{
		ePush,		//押した瞬間
		eHold,		//押している
		ePull,		//離した瞬間
		eFree,		//離している
		eStateMax,
	};
	enum E_BUTTON{
		eUp = 0,
		eDown,
		eLeft,
		eRight,
		eButton1,
		eButton2,
		eButton3,
		eButton4,
		eButton5,
		eButton6,
		eButton7,
		eMouseL,
		eMouseR,
		eMouseC,
		eMax = 16
	};
	static char	m_key_code[PAD_MAX][eMax];
	static unsigned long m_key_old[PAD_MAX];
	static unsigned long m_key_state[PAD_MAX][eStateMax];
	static CVector2D m_mouse_old;
	static CVector2D m_mouse_vec;
	static int		m_mouse_wheel;
	static int		m_mouse_wheelOld;
	static bool		m_mouse_inside;
public:
	/*!
		@brief	キーの状態を検査
		@param	no		[in] コントローラー番号
		@param	state	[in] 状態
		@param	button	[in] ボタン
		@retval	true:指定した状態　false:指定した状態ではない
	**/
	static bool GetState(int no,E_STATE state,E_BUTTON button){
		return static_cast<bool>((m_key_state[no][state] & (1<<button)) != 0);
	}
	/*!
		@brief	キーの状態を強制設定
		@param	no		[in] コントローラー番号
		@param	state	[in] 状態
		@param	button	[in] ボタン
		@retval	無し
	**/
	static void SetState(int no,E_STATE state,E_BUTTON button){
		m_key_state[no][state] |= (1<<button);
	}

	/*!
		@brief	各ボタンに対応するキーを設定
		@param	no		[in] コントローラー番号
		@param	button	[in] ボタン
		@param	code	[in] キーコード
		@retval	無し
	**/
	static void SetButton(int no,E_BUTTON button,char code){
		m_key_code[no][button] = code;
	}

	
	/*!
		@brief	マウスカーソルの座標を取得
		@retval	マウスカーソルの座標
	**/
	static CVector2D getMousePoint() {
		POINT pt;
		//マウスの現在の座標を取得する
		GetCursorPos(&pt);
		HDC glDc = wglGetCurrentDC();
		 //ウィンドウハンドル取得
		HWND hWnd = WindowFromDC(glDc);
		ScreenToClient(hWnd,&pt);

		return CVector2D(static_cast<float>(pt.x), static_cast<float>(pt.y));
	}
	
	/*!
		@brief	マウスの移動量を取得
		@retval	マウスの移動量
	**/
	static CVector2D getMouseVec() {
		return m_mouse_vec;
	}
	
	/*!
		@brief	マウスカーソルをウインドウ内に収めるフラグの設定
		@param	f		[in] true:ウインドウ内に収める
		@retval	無し
	**/
	static void setMouseInside(bool f) {
		m_mouse_inside = f;
	}

	/*!
		@brief	マウスカーソルの表示設定
		@param	f		[in] true:表示　false:非表示
		@retval	無し
	**/
	static void showCursor(bool f) {
		 ShowCursor(f);
	}
	
	/*!
		@brief	マウスホイールの変化量取得
		@retval	マウスホイールの変化量
	**/
	static int getMouseWheel() {
		return m_mouse_wheelOld;
	}
	/*!
		@brief	マウスホイールの変化量を加える
		@param	a		[in] 変化量
		@retval	無し
	**/
	static void addMouseWheel(int a) {
		m_mouse_wheel+=a;
	}
	/*!
		@brief	キーの状態を更新する
		@retval	無し
	**/
	static void UpDate();
	

};