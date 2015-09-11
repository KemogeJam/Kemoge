/*!
 *	@brief		�摜�Ǘ��N���X
 *	
 */

#pragma once

#include "CRect.h"
#include "CMatrix.h"
#include "CShader.h"
#include "CTexture.h"

class CImage{
private:

	CTexture*	m_pTexture;	//�e�N�X�`���[
	CVector2D	m_vPos;		//�ʒu(pixel)
	CVector2D	m_vCenter;	//���S�ʒu(pixel)
	CVector2D	m_vSize;	//�T�C�Y(pixel)
	CRect		srcRect;	//�\������`
	float		m_ang;		//��]�l
	bool		m_flipH;	//���E���]
	CColorRGBA	m_color;	//�F

public:
	CVector2D & getPos() { return m_vPos; }

public:
	CImage();
	~CImage();
	/*!
		@brief	�t�@�C������摜��ǂݍ��ށi24bitbmp,png�Ή��j
		@param	path		[in] �t�@�C����
		@retval	����:true�ڐG false��ڐG
	**/
	bool Load(char* path);
	
	/*!
		@brief	�摜��j������
		@retval	����
	**/
	
	void Release();

	/*!
		@brief	�\���ʒu��ݒ肷��
		@param	x		[in] ���ʒu
		@param	y		[in] �c�ʒu
		@retval	����
	**/
	void setPos(float x,float y) {
		m_vPos.x = x; m_vPos.y = y;
	}
	void setPos(CVector2D p) {
		m_vPos = p;
	}

	/*!
		@brief	��]�̒��S�ʒu��ݒ肷��
		@param	x		[in] ���ʒu
		@param	y		[in] �c�ʒu
		@retval	����
	**/
	void setCenter(float x,float y) {
		m_vCenter.x = x; m_vCenter.y = y;
	}
	void setCenter(CVector2D p) {
		m_vCenter = p;
	}

	/*!
		@brief	�\���T�C�Y��ݒ肷��
		@param	w		[in] ��
		@param	h		[in] ����
		@retval	����
	**/
	void setSize(float w,float h) {
		m_vSize.x = w; m_vSize.y = h;
	}
	void setSize(CVector2D s) {
		m_vSize = s;
	}
	/*!
		@brief	�\������`��ݒ�
		@param	left	[in] ���ʒu
		@param	top		[in] ��ʒu
		@param	right	[in] �E�ʒu
		@param	bottom	[in] ���ʒu
		@retval	����
	**/
	void setRect(int left,int top,int right,int bottom){
		srcRect.m_left = static_cast<float>(left);
		srcRect.m_right = static_cast<float>(right);
		srcRect.m_top = static_cast<float>(top);
		srcRect.m_bottom = static_cast<float>(bottom);
	}

	/*!
		@brief	��]�l��ݒ�
		@param	ang		[in] ��]�l
		@retval	����
	**/
	void setAng(float ang){
		m_ang = ang;
	}

	/*!
		@brief	���E���]�t���O��ݒ�
		@param	f		[in] true:�ʏ� false:�������]
		@retval	����
	**/
	void setFlipH(bool f) {
		m_flipH = f;
	}

	/*!
		@brief	�F��ݒ�
		@param	r		[in] �Ԑ���
		@param	g		[in] �ΐ���
		@param	b		[in] ����
		@param	a		[in] �s�����x
		@retval	����
	**/
	void setColor(float r, float g, float b,float a){
		m_color.r = r;
		m_color.g = g;
		m_color.b = b;
		m_color.a = a;
	}
	/*!
		@brief	�`����s��
		@retval	����
	**/
	void Draw();
};