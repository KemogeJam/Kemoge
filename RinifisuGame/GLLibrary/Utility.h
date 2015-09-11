
#include "GL.h"
#include "CMatrix.h"
#include <cmath>

namespace Utility {
	/*!
		@brief	Degree�i�x�j��Radian�ɕϊ�
		@param	d				[in] �p�x
		@retval	Radian�ɕϊ����ꂽ�p�x
	**/

	inline float DgreeToRadian(float d) {
		return d*static_cast<float>(M_PI) /180.0f;
	}
	/*!
		@brief	�p�x�̐��K��
		@param	a				[in] �p�x
		@retval	-PI�`PI
	**/

	inline float NormalizeAngle(float a) {
		if(a>static_cast<float>(M_PI)) return a- static_cast<float>(M_PI) * 2.0f;
		else if(a<-static_cast<float>(M_PI)) return a+ static_cast<float>(M_PI) * 2.0f;
		return a;
	}
	/*!
		@brief	�p�x�̍����擾
		@param	a			[in] �p�x
		@param	b			[in] �p�x
		@retval	a��b�̊p�x�̍�
	**/

	inline float DiffAngle(float a,float b) {
		if(a*b < 0.0f){
			if(abs(a)+abs(b) > static_cast<float>(M_PI)) {
				if(b<0.0f) a-= static_cast<float>(M_PI) *2.0f;
				else a+= static_cast<float>(M_PI) *2.0f;
			}
		}
		return b-a;
	}
	/*!
		@brief	�����擾
		@param	min				[in] �Œ�l
		@param	max				[in] �ő�l
		@retval	�Œ�l�`�ő�l�̗���
	**/

	template <typename T> inline T Rand(T min,T max) {
		return min + ((max-min) * rand()/ RAND_MAX);
	}
	/*!
		@brief	�X�N���[�����W�ϊ������[���h���W
		@param	out				[out] ���[���h���W
		@param	spos			[in] �X�N���[�����W
		@param	mProj			[in] �ˉe�s��
		@param	mView			[in] �r���[�s��
		@param	w				[in] �X�N���[����
		@param	h				[in] �X�N���[������
		@retval	����
	**/
	void ScreenToWorld(CVector3D *out,CVector3D spos,CMatrix mProj,CMatrix mView,int w,int h);
	/*!
		@brief	���[���h���W���X�N���[�����W�ϊ�
		@param	out				[out] �X�N���[�����W
		@param	wpos			[in] ���[���h���W
		@param	mProj			[in] �ˉe�s��
		@param	mView			[in] �r���[�s��
		@param	w				[in] �X�N���[����
		@param	h				[in] �X�N���[������
		@retval	����
	**/
	void WorldToScreen(CVector3D *out,CVector3D wpos,CMatrix mProj,CMatrix mView,int w,int h);
}