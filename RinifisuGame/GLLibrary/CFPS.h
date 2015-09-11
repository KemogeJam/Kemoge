/*!
 *	@brief		FPS制御クラス
 *	
 */
#pragma once

#include <time.h>
#include <windows.h>

class CFPS {
	//時間計測用
	static LARGE_INTEGER freq;
	static LARGE_INTEGER time_buf;
	static int fps;
public:
	/*!
		@brief	初期化を行う
		@retval	無し
	**/
	static void Init();

	/*!
		@brief	６０FPSになるよう待機する
		@retval	無し
	**/
	static void Wait();

	/*!
		@brief	現在のFPSを取得
		@retval	FPS
	**/
	static int getFPS(){ return fps;}

};