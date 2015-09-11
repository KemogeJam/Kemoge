/*!
*	@brief	�L�[���̓N���X
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
		ePush,		//�������u��
		eHold,		//�����Ă���
		ePull,		//�������u��
		eFree,		//�����Ă���
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
		@brief	�L�[�̏�Ԃ�����
		@param	no		[in] �R���g���[���[�ԍ�
		@param	state	[in] ���
		@param	button	[in] �{�^��
		@retval	true:�w�肵����ԁ@false:�w�肵����Ԃł͂Ȃ�
	**/
	static bool GetState(int no,E_STATE state,E_BUTTON button){
		return static_cast<bool>((m_key_state[no][state] & (1<<button)) != 0);
	}
	/*!
		@brief	�L�[�̏�Ԃ������ݒ�
		@param	no		[in] �R���g���[���[�ԍ�
		@param	state	[in] ���
		@param	button	[in] �{�^��
		@retval	����
	**/
	static void SetState(int no,E_STATE state,E_BUTTON button){
		m_key_state[no][state] |= (1<<button);
	}

	/*!
		@brief	�e�{�^���ɑΉ�����L�[��ݒ�
		@param	no		[in] �R���g���[���[�ԍ�
		@param	button	[in] �{�^��
		@param	code	[in] �L�[�R�[�h
		@retval	����
	**/
	static void SetButton(int no,E_BUTTON button,char code){
		m_key_code[no][button] = code;
	}

	
	/*!
		@brief	�}�E�X�J�[�\���̍��W���擾
		@retval	�}�E�X�J�[�\���̍��W
	**/
	static CVector2D getMousePoint() {
		POINT pt;
		//�}�E�X�̌��݂̍��W���擾����
		GetCursorPos(&pt);
		HDC glDc = wglGetCurrentDC();
		 //�E�B���h�E�n���h���擾
		HWND hWnd = WindowFromDC(glDc);
		ScreenToClient(hWnd,&pt);

		return CVector2D(static_cast<float>(pt.x), static_cast<float>(pt.y));
	}
	
	/*!
		@brief	�}�E�X�̈ړ��ʂ��擾
		@retval	�}�E�X�̈ړ���
	**/
	static CVector2D getMouseVec() {
		return m_mouse_vec;
	}
	
	/*!
		@brief	�}�E�X�J�[�\�����E�C���h�E���Ɏ��߂�t���O�̐ݒ�
		@param	f		[in] true:�E�C���h�E���Ɏ��߂�
		@retval	����
	**/
	static void setMouseInside(bool f) {
		m_mouse_inside = f;
	}

	/*!
		@brief	�}�E�X�J�[�\���̕\���ݒ�
		@param	f		[in] true:�\���@false:��\��
		@retval	����
	**/
	static void showCursor(bool f) {
		 ShowCursor(f);
	}
	
	/*!
		@brief	�}�E�X�z�C�[���̕ω��ʎ擾
		@retval	�}�E�X�z�C�[���̕ω���
	**/
	static int getMouseWheel() {
		return m_mouse_wheelOld;
	}
	/*!
		@brief	�}�E�X�z�C�[���̕ω��ʂ�������
		@param	a		[in] �ω���
		@retval	����
	**/
	static void addMouseWheel(int a) {
		m_mouse_wheel+=a;
	}
	/*!
		@brief	�L�[�̏�Ԃ��X�V����
		@retval	����
	**/
	static void UpDate();
	

};