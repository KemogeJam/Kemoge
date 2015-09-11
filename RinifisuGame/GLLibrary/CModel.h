/*!
*	@brief	���f���̊�{�N���X
*
*
**/
#pragma once

#include "CMatrix.h"
#include "CShader.h"

class CModel {
public:
	CVector3D m_pos;	//���W		
	CVector3D m_rot;	//��]�l
	CVector3D m_scale;	//�X�P�[���l
	
	CVector3D m_baserot;	//��]�l

	CMatrix m_matrix;	//���[���h�i���f���j�s��
	CMatrix m_transMtx;	//���s�ړ��s��
	CMatrix m_rotMtx;	//��]�s��
	CMatrix m_scaleMtx;	//�X�P�[�����O�s��

	
	CShader		*m_shader;	//�V�F�[�_�[

public:
	/*!
		@brief	�R���X�g���N�^

	**/
	CModel() : m_pos(0,0,0),m_rot(0,0,0),m_scale(1,1,1),m_baserot(0,0,0) {
	}

	/*!
		@brief	���W��ݒ肷��
		@param	pos				[in] ���W
		@retval	����
	**/
	void setPos(CVector3D pos){
		m_pos = pos;
	}
	/*!
		@brief	���W��ݒ肷��
		@param	x				[in] x���W
		@param	y				[in] y���W
		@param	z				[in] z���W
		@retval	����
	**/
	void setPos(float x,float y,float z){
		m_pos.x = x;
		m_pos.y = y;
		m_pos.z = z;
	}	

	/*!
		@brief	���W���擾����
		@retval ���W
	**/
	CVector3D getPos(){
		return m_pos;
	}
	/*!
		@brief	��]�l��ݒ肷��
		@param	rot				[in] ��]�l
		@retval	����
	**/

	void setRot(CVector3D rot){
		m_rot = rot;
	}

	/*!
		@brief	��b��]�l��ݒ肷��(���f�����O��t�ɂȂ��Ă��铙�p)
		@param	x				[in] x����]�l
		@param	y				[in] y����]�l
		@param	z				[in] z����]�l
		@retval	����
	**/
	void seBasetRot(float x,float y,float z){
		m_baserot.x = x;
		m_baserot.y = y;
		m_baserot.z = z;
	}
	/*!
		@brief	��]�l��ݒ肷��
		@param	x				[in] x����]�l
		@param	y				[in] y����]�l
		@param	z				[in] z����]�l
		@retval	����
	**/
	void setRot(float x,float y,float z){
		m_rot.x = x;
		m_rot.y = y;
		m_rot.z = z;
	}

	/*!
		@brief	��]�l���擾����
		@retval	��]�l
	**/
	CVector3D getRot(){
		return m_rot;
	}

	/*!
		@brief	�X�P�[����ݒ肷��
		@param	scale			[in] �X�P�[���l
		@retval	����
	**/

	void setScale(CVector3D scale){
		m_scale = scale;
	}
	
	/*!
		@brief	�X�P�[���l��ݒ肷��
		@param	x				[in] x���X�P�[��
		@param	y				[in] y���X�P�[��
		@param	z				[in] z���X�P�[��
		@retval	����
	**/
	void setScale(float x,float y,float z){
		m_scale.x = x;
		m_scale.y = y;
		m_scale.z = z;
	}

	/*!
		@brief	�X�P�[���l���擾��
		@retval	�X�P�[���l
	**/
	CVector3D getScale(){
		return m_scale;
	}

	/*!
		@brief	���s�ړ��s����擾����
		@retval	���s�ړ����s��
	**/
	CMatrix getTransMatrix() {
		return m_transMtx;
	}

	/*!
		@brief	��]�s����擾����
		@retval	��]�s��
	**/
	CMatrix getRotMatrix() {
		return m_rotMtx;
	}
	/*!
		@brief	�X�P�[�����O�s����擾����
		@retval	�X�P�[�����O�s��
	**/
	CMatrix getScaleMatrix() {
		return m_scaleMtx;
	}

	/*!
		@brief	���W�A��]�l�A�X�P�[���l���烏�[���h�s����쐬����
		@retval	����
	**/
	void UpdateMatrix();

	/*!
		@brief	���[���h�s���ݒ肷��
		@param	m				[in] �s��
		@retval	����
	**/
	void setMatrix(CMatrix &m){
		m_matrix = m;
	}
	/*!
		@brief�@���[���h�s����擾����
		@retval	���[���h�s��
	**/
	CMatrix getMatrix(){
		return m_matrix;
	}

	/*!
		@brief	�t�@�C�����烂�f����ǂݍ���
		@retval	���ʁ@true���� false���s
	**/
	virtual bool Load(const char *path)=0;
	
	/*!
		@brief	�s����w�肵�ĕ`�悷��
		@param	m				[in] ���[���h�s��
		@retval	����
	**/
	virtual void RenderM(CMatrix &m)=0;

	/*!
		@brief	�`�悷��
		@retval	����
	**/
	virtual void Render(){
		UpdateMatrix();
		RenderM(m_matrix);
	}
	/*!
		@brief	�`�悷��
		@retval	����
	**/
	virtual void RenderBuilbord(CMatrix m){
		UpdateMatrix();
		RenderM(m_matrix*m);
	}


	/*!
		@brief	���f����j������
		@retval	����
	**/
	virtual void Release()=0;

	
	virtual void SendShaderParam();


};