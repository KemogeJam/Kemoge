#include "CInput.h"


char		CInput::m_key_code[PAD_MAX][CInput::eMax] = { 0 };
unsigned long CInput::m_key_old[PAD_MAX] = { 0 };
unsigned long CInput::m_key_state[PAD_MAX][CInput::eStateMax] = { 0 };
CVector2D CInput::m_mouse_old = CVector2D(0, 0);
CVector2D CInput::m_mouse_vec;
int CInput::m_mouse_wheel = 0;
int CInput::m_mouse_wheelOld = 0;
bool CInput::m_mouse_inside = false;
void CInput::UpDate() {
	for (int i = 0; i < PAD_MAX; i++) {
		unsigned long key = 0;
		unsigned long state = 0;
		for (int j = 0; j < eMax; j++) {
			if (::GetKeyState(m_key_code[i][j]) & 0x80) {
				key |= 1 << j;
			}
		}
		m_key_state[i][ePush] = (~m_key_old[i]) & key;
		m_key_state[i][eHold] = m_key_old[i] & key;
		m_key_state[i][ePull] = m_key_old[i] & (~key);
		m_key_state[i][eFree] = (~m_key_old[i]) & (~key);
		m_key_old[i] = key;
	}
	CVector2D mouse_pos;
	mouse_pos = getMousePoint();
	m_mouse_vec = mouse_pos - m_mouse_old;
	if (m_mouse_inside) {
		//ƒJ[ƒ\ƒ‹‚ð‰æ–Ê“à‚É–ß‚·
		HDC glDc = wglGetCurrentDC();
		HWND hWnd = WindowFromDC(glDc);
		RECT rect;
		if (GetClientRect(hWnd, &rect)) {
			if (mouse_pos.x > rect.right) {
				mouse_pos.x = 0;
			}
			else if (mouse_pos.x < 0) {
				mouse_pos.x = static_cast<float>(rect.right);
			}
			if (mouse_pos.y > rect.bottom) {
				mouse_pos.y = 0;
			}
			else if (mouse_pos.y < 0) {
				mouse_pos.y = static_cast<float>(rect.bottom);
			}
			POINT pt = { static_cast<LONG>(mouse_pos.x),static_cast<LONG>(mouse_pos.y) };
			ClientToScreen(hWnd, &pt);
			SetCursorPos(pt.x, pt.y);
		}
	}
	m_mouse_old = mouse_pos;
	m_mouse_wheelOld = m_mouse_wheel;
	m_mouse_wheel = 0;

}
