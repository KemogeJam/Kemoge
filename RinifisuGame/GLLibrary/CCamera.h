/*!
 *	@brief		�J�����N���X
 *	5�̃J���������݂���B
 *�@�J�����g�J�����ɐݒ肵���r���[�s��Ń��f�����\�������B
 */
#pragma once

#include "CVector.h"
#include "CMatrix.h"
#include "CRect.h"
class CCamera {
private:
	CVector3D m_pos;	//�J�����̈ʒu
	CVector3D m_at;		//�����_
	CVector3D m_up;		//Up�x�N�g��
	CVector3D m_dir;	//�����iFront�x�N�g���j
	CMatrix m_mView;	//�J�����s��
	CMatrix m_mProj;	//�ˉe�s��
	float	m_whidth;	//�J�����̕�
	float	m_height;	//�@�V�@�@����
	static CCamera m_camera[5];
	static CCamera *m_pCurrent;
	CRect	m_screen;
public:

	/*!
		@brief	�J�����I�u�W�F�N�g���擾
		@param	num			[in] �擾����J�����̔ԍ�
		@retval	�J�����I�u�W�F�N�g�̃A�h���X
	**/
	static CCamera* getCamera(int num=0);
	
	/*!
		@brief	���ݎg�p���Ă���J�����I�u�W�F�N�g���擾
		@retval	�J�����g�J�����I�u�W�F�N�g�̃A�h���X
	**/
	static CCamera* getCurrent();

	/*!
		@brief	�g�p����J�����ɐݒ�
		@param	num			[in] �g�p����J�����̔ԍ�
		@retval�@����
	**/

	static void setCurrent(int num);
	/*!
		@brief	�g�p����J�����ɐݒ�
		@param	p			[in] �g�p����J�����̃A�h���X
		@retval�@����
	**/
	static void setCurrent(CCamera *p);
	/*!
		@brief	�R���X�g���N�^
		@retval�@����
	**/
	CCamera();
	/*!
		@brief	�J�����̕����擾
		@retval�@�J�����̕��@
	**/
	float getWhidth();
	/*!
		@brief	�J�����̍������擾
		@retval�@�J�����̍����@
	**/
	float getHeight();
	/*!
		@brief	�J�����̕��ƍ����ݒ�
		@param	w			[in] ��
		@param	h			[in] ����
		@retval�@�����@
	**/
	void SetSize(float w,float h);

	/*!
		@brief	�����J�����Ńr���[�s��
		@param	eye			[in] �ʒu
		@param	at			[in] �����_
		@param	up			[in] ��x�N�g��
		@retval�@�����@
	**/
	void LookAt(CVector3D &eye,CVector3D &at,CVector3D &up);

	/*!
		@brief	�ʒu�Ɖ�]�l�Ńr���[�s���ݒ�
		@param	pos			[in] �ʒu
		@param	rot			[in] ��]�l
		@retval�@�����@
	**/
	void setTranseRot(CVector3D &pos,CVector3D &rot);
	/*!
		@brief	���f���s�񂩂�r���[�s���ݒ�
		@param	mtx			[in] ���f���s��
		@retval�@�����@
	**/
	void setTranseRot(CMatrix &mtx);

	/*!
		@brief	�r���[�s��𒼐ڐݒ�
		@param	m			[in] �r���[�s��
		@retval�@�����@
	**/
	void setMatrix(CMatrix &m);

	/*!
		@brief	�r���[�s����擾
		@retval�@�����@
	**/
	CMatrix getMatrix();

	
	/*!
		@brief	�r���[�s����擾
		@retval�@�����@
	**/
	CMatrix getBuilbordMatrix();
	
	/*!
		@brief	�J�����̈ʒu���擾
		@retval�@�J�����̈ʒu
	**/
	CVector3D getPos();

	/*!
		@brief	�J�����̌������擾
		@retval�@�J�����̌���
	**/
	CVector3D getDir();


	/*!
		@brief	�ˉe�s��̐ݒ�
		@param	m			[in] �ˉe�s��
	**/
	void setProjectionMatrix(CMatrix &m) {
		m_mProj = m;
	}
	/*!
		@brief	 �ˉe�s����擾
		@retval�@�ˉe�s��
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