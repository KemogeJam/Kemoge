#pragma once
#include "GL.h"
#include "CVector.h"
struct SMatrix
{
	union
	{
		float	f[16];
		float	m[4][4];
		struct
		{
			float	m00,m10,m20,m30,
					m01,m11,m21,m31,
					m02,m12,m22,m32,
					m03,m13,m23,m33;
		};
	};
};
class CMatrix : public SMatrix {
public:
	CMatrix() {
		SetIndentity();
	}
	CMatrix(float mat00,float mat01,float mat02,float mat03,
			float mat10,float mat11,float mat12,float mat13,
			float mat20,float mat21,float mat22,float mat23,
			float mat30,float mat31,float mat32,float mat33) {
				m00 = mat00; m01 = mat01; m02 = mat02; m03 = mat03;
				m10 = mat10; m11 = mat11; m12 = mat12; m13 = mat13;
				m20 = mat20; m21 = mat21; m22 = mat22; m23 = mat23;
				m30 = mat30; m31 = mat31; m32 = mat32; m33 = mat33;
	}
	//単位行列を設定
	void SetIndentity();
	//平行移動行列を設定
	void Transelate(float x,float y, float z);
	//スケール行列を設定
	void Scale(float x,float y, float z);
	//クオータニオン→行列
	void setQuaternion(float x,float y, float z,float w);
	//回転行列を設定
	void RotationX(float r);
	void RotationY(float r);
	void RotationZ(float r);
	//任意軸で回転行列を設定
	void RotationAxis(float vx,float vy,float vz,float r);
	//カメラ行列用
	void LookAt(const CVector3D& eye,const CVector3D& at,const CVector3D& up);
	//透視投影行列用
	void Perspective(float fovy,float aspect,float zNear,float zFar);

	//ビューポート行列用
	void Viewport(float x,float y,float w,float h);


	//逆行列を取得
	CMatrix getInverse( void );

	//各種演算
	CMatrix operator +(const CMatrix& num);
	CMatrix operator *(CMatrix num);
	CMatrix operator *(const float num);


	CVector4D operator *(const CVector4D num);
	CVector3D operator *(const CVector3D num);

	CVector3D getFront() {return CVector3D(m02,m12,m22);}
	CVector3D getUp() {return CVector3D(m01,m11,m21);}
	CVector3D getRight() {return CVector3D(m00,m10,m20);}
	CVector3D getTranse() {return CVector3D(m03,m13,m23);}

};
CMatrix operator *(const float num,const CMatrix mtr);
CVector4D operator * (const CVector4D num,const CMatrix mtr);
CVector3D operator * (const CVector3D num,const CMatrix mtr);