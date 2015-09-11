#pragma once

#include "CMatrix.h"
/*!
 *	@brief		OBB�N���X
 *	
 *	OBB�̃p�����[�^�N���X
 */
class COBB {
public:
	CVector3D m_center;		//���S���W
	CVector3D m_base_center;		//���S���W
	CVector3D m_axis[3];	//�e���x�N�g��
	float	 m_length[3];	//�e���̒���
	CMatrix m_mat;
	COBB() {
	}
	COBB(CVector3D center,CVector3D axis_x,CVector3D axis_y,CVector3D axis_z,float lengthX,float lengthY,float lengthZ) {
		m_base_center = m_center = center;
		m_axis[0] = axis_x;m_axis[1] = axis_y;m_axis[2] = axis_z;
		m_length[0] = lengthX;m_length[1] = lengthY;m_length[2] = lengthZ;
	}
	//OBB�ɍs��𔽉f
	void Transeform(CMatrix &mat,bool trans=false);
	/*
		@brief	����e�X�g�pOBB�̕\��
		@retval	����
	*/
	void Draw();
};

/*!
 *	@brief		�Փ˔���N���X
 *
 */
class CCollision {
private:
	/*!
		@brief	separate����ɓ��e����OBB���m���ڐG���Ă��邩���ׂ�
		@param	A			[in] �ՓˑΏ�OBB
		@param	B			[in] �ՓˑΏ�OBB
		@param	distVec		[in] A�̒��S����B�̒��S�܂ł̃x�N�g��
		@param	separate	[in] �������A���e���s����
		@retval	����:true�ڐG false��ڐG
	**/
	static bool CompareLength(const COBB &A,const COBB &B,const CVector3D &distVec,const CVector3D &separate,float *length=NULL);
public:
	/*!
		@brief	�����m�̏Փ˔���
		@param	centerA		[in] �P�ڂ̋��̒��S�ʒu
		@param	radiusA		[in] �P�ڂ̋��̔��a
		@param	centerB		[in] �Q�ڂ̋��̒��S�ʒu
		@param	radiusB		[in] �Q�ڂ̋��̔��a
		@retval	����:true�ڐG false��ڐG
	**/
	static bool CollisionShpere(const CVector3D &centerA,float radiusA,const CVector3D &centerB,float radiusB);
	/*!
		@brief	AABB���m�̏Փ˔���
		@param	minA		[in] �P�ڂ�AABB�̍ŏ��ʒu
		@param	maxA		[in] �P�ڂ�AABB�̍ő�ʒu
		@param	minB		[in] �Q�ڂ�AABB�̍ŏ��ʒu
		@param	maxB		[in] �Q�ڂ�AABB�̍ő�ʒu
		@retval	����:true�ڐG false��ڐG
	**/
	static bool CollisionAABB(const CVector3D &minA,const CVector3D &maxA,const CVector3D &minB,const CVector3D &maxB);
	/*!
		@brief	OBB���m�̏Փ˔���
		@param	A			[in] �P�ڂ�OBB
		@param	B			[in] �Q�ڂ�OBB
		@retval	����:true�ڐG false��ڐG
	**/
	static bool CollisionOBB(const COBB &A,const COBB &B);
	/*!
		@brief	OBB�Ƌ��̏Փ˔���
		@param	A			[in] OBB
		@param	cneter		[in] ���̒��S
		@param	radius		[in] ���̔��a
		@retval	����:true�ڐG false��ڐG
	**/
	static bool CollisionOBBShpere(const COBB &A,const CVector3D &cener , float radius);
	
	/*!
		@brief	�J�v�Z���Ƌ��̏Փ˔���
		@param�@c_top		[in] �J�v�Z���J�n�n�_
		@param�@c_bottom	[in] �J�v�Z���I���n�_
		@param	c_radius	[in] �J�v�Z���̔��a
		@param	s_cneter	[in] ���̒��S
		@param	s_radius	[in] ���̔��a
		@retval	����:true�ڐG false��ڐG
	**/
	static bool CollisionCapsuleShpere(const CVector3D &c_top,const CVector3D &c_bottom,float c_radius,const CVector3D &s_center , float s_radius);
	
	/*!
		@brief	�J�v�Z�����m�̏Փ˔���
		@param�@top1		[in] �J�v�Z���J�n�n�_
		@param�@bottom1		[in] �J�v�Z���I���n�_
		@param	radius1		[in] �J�v�Z���̔��a
		@param�@top2		[in] �J�v�Z���J�n�n�_
		@param�@bottom2		[in] �J�v�Z���I���n�_
		@param	radius2		[in] �J�v�Z���̔��a
		@retval	����:true�ڐG false��ڐG
	**/
	static bool CollisionCapsule(const CVector3D &top1,const CVector3D &bottom1,float radius1,const CVector3D &top2,const CVector3D &bottom2,float radius2);

	/*!
		@brief	�_C���O�p�`�|���S����ɂ��邩���ׂ�
		@param	C			[in] �_�̍��W
		@param	V0			[in] �O�p�`�|���S���̒��_1
		@param	V1			[in] �O�p�`�|���S���̒��_2
		@param	V2			[in] �O�p�`�|���S���̒��_3
		@param	N			[in] �O�p�`�|���S���̖@��
		@retval	����:true�ڐG false��ڐG
	**/
	static bool TriangleIntersect(const CVector3D &c,const CVector3D &v0,const  CVector3D &v1, const CVector3D &v2,const CVector3D &n);
	/*!
		@brief	�����ƎO�p�`�|���S���Ƃ̏Փ˔���
		@param	C			[out] �ڐG�n�_
		@param	S			[in] �����̊J�n�ʒu
		@param	E			[in] �����̏I���ʒu
		@param	V0			[in] �O�p�`�|���S���̒��_1
		@param	V1			[in] �O�p�`�|���S���̒��_2
		@param	V2			[in] �O�p�`�|���S���̒��_3
		@retval	����:true�ڐG false��ڐG
	**/
	static bool IntersectTriangleRay(CVector3D *corss,const CVector3D &p1,const  CVector3D &p2,const CVector3D& v0,const  CVector3D &v1,const  CVector3D &v2,float *pt );

	/*!
		@brief	point����߂�v0��v1����̓_�𒲂ׂ�
		@param	V0			[in] �����̊J�n�ʒu
		@param	V1			[in] �����̏I���ʒu
		@param	point		[in] �_
		@retval	����:true�ڐG false��ڐG
	**/
	static CVector3D PointOnLineSegmentNearestPoint(const CVector3D &v0,const CVector3D &v1,const CVector3D &point);
	
	/*!
		@brief	point����߂�v0��v1����̓_�𒲂ׂ�i�񎟌��p�j
		@param	V0			[in] �����̊J�n�ʒu
		@param	V1			[in] �����̏I���ʒu
		@param	point		[in] �_
		@retval	����:true�ڐG false��ڐG
	**/
	static CVector2D PointOnLineSegmentNearestPoint(const CVector2D &v0,const CVector2D &v1,const CVector2D &point);

	/*!
		@brief	�O�p�|���S���Ƌ��̏Փ˔���
		@param	V0			[in] �O�p�`�|���S���̒��_1
		@param	V1			[in] �O�p�`�|���S���̒��_2
		@param	V2			[in] �O�p�`�|���S���̒��_3
		@param	cneter		[in] ���̒��S
		@param	rudius		[in] ���̔��a
		@param	cross		[out] �ŒZ�ڐG�_
		@param	length		[out] �ŒZ����
		@retval	����:true�ڐG false��ڐG
	**/
	static bool CollisionTriangleSphere(const CVector3D &v0,const CVector3D &v1,const CVector3D &v2,const CVector3D &center,float radius,CVector3D *cross=0,float *length = 0);

	/*!
		@brief	�O�p�|���S���ƃJ�v�Z���̏Փ˔���
		@param	V0			[in] �O�p�`�|���S���̒��_1
		@param	V1			[in] �O�p�`�|���S���̒��_2
		@param	V2			[in] �O�p�`�|���S���̒��_3
		@param	cneter		[in] ���̒��S
		@param	rudius		[in] ���̔��a
		@param	cross		[out] �ŒZ�ڐG�_
		@param	length		[out] �ŒZ����
		@retval	����:true�ڐG false��ڐG
	**/
	static bool CollisionTriangleCapsule(const CVector3D &v0,const CVector3D &v1,const CVector3D &v2,const CVector3D &top,const CVector3D &bottom,float radius,CVector3D *cross=0,float *length = 0);


	/*!
		@brief	2�����Ԃ̋���
		@param	s1			[in] �����P�̊J�n�n�_
		@param	e1			[in] �����P�̏I���n�_
		@param	s2			[in] �����Q�̊J�n�n�_
		@param	e2			[in] �����Q�̏I���n�_
		@param	c1			[out] �����P��ł̍ŒZ�n�_�i�������j
		@param	c2			[out] �����Q��ł̍ŒZ�n�_�i�������j
		@retval	����
	**/
	static float DistanceLine(const CVector3D &s1,const CVector3D &e1,const CVector3D &s2,const CVector3D &e2,CVector3D *c1=NULL,CVector3D *c2=NULL);


	/*!
		@brief	�_�Ɛ��̋���
		@param	v0			[in] �����̊J�n�n�_
		@param	v1			[in] �����̏I���n�_
		@param	p			[in] �_
		@retval�@����
	**/
	static float DistancePointToLine(const CVector3D &v0,const CVector3D &v1,const CVector3D &p);
	/*!
		@brief	�_�Ɛ��̋����̓��
		@param	v0			[in] �����̊J�n�n�_
		@param	v1			[in] �����̏I���n�_
		@param	p			[in] �_
		@retval�@�����̓��
	**/
	static float DistancePointToLineSq(const CVector3D &v0,const CVector3D &v1,const CVector3D &p);

};