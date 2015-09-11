/*!
 *	@brief		FPS����N���X
 *	
 */
#pragma once

#include <time.h>
#include <windows.h>

class CFPS {
	//���Ԍv���p
	static LARGE_INTEGER freq;
	static LARGE_INTEGER time_buf;
	static int fps;
public:
	/*!
		@brief	���������s��
		@retval	����
	**/
	static void Init();

	/*!
		@brief	�U�OFPS�ɂȂ�悤�ҋ@����
		@retval	����
	**/
	static void Wait();

	/*!
		@brief	���݂�FPS���擾
		@retval	FPS
	**/
	static int getFPS(){ return fps;}

};