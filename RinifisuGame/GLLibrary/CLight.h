
/*!
*		@brief	�V�F�[�_�[�p�����N���X
*
**/
#pragma once
#include "GL.h"
#include "CVector.h"


class CLight {
public:
	enum {
		eLight_None=0,		//��������
		eLight_Direction,	//����
		eLight_Point,		//�S�����|�C���g��
		eLight_Spot,		//�X�|�b�g���C�g
	};
	static const int LIGHT_MAX = 5;
	static CVector3D	m_lightPos[LIGHT_MAX];
	static CVector3D	m_lightDir[LIGHT_MAX];
	static CVector3D	m_AmbientColor[LIGHT_MAX];
	static CVector3D	m_DiffuseColor[LIGHT_MAX];
	static int			m_Type[LIGHT_MAX];
	static float		m_Attenuation[LIGHT_MAX];
	static float		m_RadiationAngle[LIGHT_MAX];
	static int			m_Lighting;
	
private:
public:
	
	/*!
		@brief	�����̗L����ݒ肷��
		@retval	����
	**/
	static void setLighting(bool f){
		if(f) m_Lighting = 1;
		else m_Lighting=0;
	}
	/*!
		@brief	�����̗L�����擾����
		@retval	
	**/
	static int getLighting(){
		return m_Lighting;
	}
	/*!
		@brief	�����̈ʒu��ݒ肷��
		@param	no		[in] �����ԍ�
		@param	v		[in] �ʒu
		@retval	����
	**/
	static void setPos(int no,CVector3D v){
		m_lightPos[no] = v;
	}

	/*!
		@brief	�����̌�����ݒ肷��
		@param	no		[in] �����ԍ�
		@param	v		[in] �����x�N�g��
		@retval	����
	**/
	static void setDir(int no,CVector3D v){
		m_lightDir[no] = v;
	}

	
	/*!
		@brief	�����̎�ނ�ݒ肷��
		@param	no		[in] �����ԍ�
		@param	type	[in] �����̎��
		@retval	����
	**/
	static void setType(int no,int type){
		m_Type[no] = type;
	}

	
	/*!
		@brief	�����̌�������ݒ肷��
		@param	no				[in] �����ԍ�
		@param	Attenuation		[in] ������
		@retval	����
	**/
	static void setAttenuation(int no,float Attenuation){
		m_Attenuation[no] = Attenuation;
	}

	/*!
		@brief	�����̍L�p��ݒ肷��
		@param	no				[in] �����ԍ�
		@param	RadiationAngle	[in] �p�x
		@retval	����
	**/
	static void setRadiationAngle(int no,float RadiationAngle){
		m_RadiationAngle[no] = RadiationAngle;
	}

	/*!
		@brief	�����̐F��ݒ肷��
		@param	no				[in] �����ԍ�
		@param	a				[in] �A���r�G���g�i�����j
		@param	d				[in] �f�t���[�Y�i�g�U���ˌ��j
		@retval	����
	**/
	static void setColor(int no,CVector3D a,CVector3D d){
		m_AmbientColor[no]  = a;
		m_DiffuseColor[no]  = d;
	}


	/*!
		@brief	�����̈ʒu���擾����
		@param	no				[in] �����ԍ�
		@retval	�ʒu
	**/
	static CVector3D getPos(int no){
		return m_lightPos[no];
	}
	
	/*!
		@brief	�����̃A���r�G���g�J���[���擾����
		@param	no				[in] �����ԍ�
		@retval	�A���r�G���g�i�����j
	**/
	static CVector3D getAmbientColor(int no){
		return m_AmbientColor[no];
	}
	
	/*!
		@brief	�����̃f�t���[�Y�J���[���擾����
		@param	no				[in] �����ԍ�
		@retval	�f�t���[�Y�i�g�U���ˌ��j
	**/
	static CVector3D getDiffuseColor(int no){
		return m_DiffuseColor[no];
	}


	
	/*!
		@brief	�����̈ʒu�z��̃A�h���X���擾����i�V�F�[�_�[�p�j
		@retval	�ʒu�z��̃A�h���X
	**/
	static CVector3D *getPosPointer(){
		return m_lightPos;
	}

	/*!
		@brief	�����̌����z��̃A�h���X���擾����i�V�F�[�_�[�p�j
		@retval	�����z��̃A�h���X
	**/
	static CVector3D *getDirPointer(){
		return m_lightDir;
	}

	
	/*!
		@brief	�����̃A���r�G���g�J���[�z��̃A�h���X���擾����i�V�F�[�_�[�p�j
		@retval	�A���r�G���g�J���[�z��̃A�h���X
	**/
	static CVector3D *getAmbientColorPointer(){
		return m_AmbientColor;
	}
	
	/*!
		@brief	�����̃f�t���[�Y�J���[�z��̃A�h���X���擾����i�V�F�[�_�[�p�j
		@retval	�f�t���[�Y�J���[�z��̃A�h���X
	**/
	static CVector3D *getDiffuseColorPointer(){
		return m_DiffuseColor;
	}
	
	/*!
		@brief	�����̎�ޔz��̃A�h���X���擾����i�V�F�[�_�[�p�j
		@retval	��ޔz��̃A�h���X
	**/
	static int *getTypeColorPointer(){
		return m_Type;
	}
	
	/*!
		@brief	�����̌������z��̃A�h���X���擾����i�V�F�[�_�[�p�j
		@retval	�������z��̃A�h���X
	**/
	static float *getAttenuationPointer(){
		return m_Attenuation;
	}

	
	/*!
		@brief	�����̍L�p�z��̃A�h���X���擾����i�V�F�[�_�[�p�j
		@retval	�L�p�z��̃A�h���X
	**/
	static float *getRadiationAnglePointer(){
		return m_RadiationAngle;
	}

};