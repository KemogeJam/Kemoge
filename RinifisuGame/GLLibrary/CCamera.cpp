#include "CCamera.h"

CCamera CCamera::m_camera[5];
CCamera* CCamera::m_pCurrent = &m_camera[0];


//�J�����I�u�W�F�N�g���擾
CCamera* CCamera::getCamera(int num) {
	return &m_camera[num];
}
//�J�����I�u�W�F�N�g���擾
CCamera* CCamera::getCurrent() {
	return m_pCurrent;
}
//�J�����I�u�W�F�N�g���擾
void CCamera::setCurrent(int num) {
	m_pCurrent = &m_camera[num];
}
//�J�����I�u�W�F�N�g���擾
void CCamera::setCurrent(CCamera *p) {
	m_pCurrent = p;
}
//�R���X�g���N�^
CCamera::CCamera(){
}
//�����擾
float CCamera::getWhidth() {
	return m_whidth;
}
//�������擾
float CCamera::getHeight() {
	return m_height;
}
//���ƍ�����ݒ�
void CCamera::SetSize(float w,float h) {
	m_whidth = w;
	m_height = h;
}
//�����J�����Ńr���[�s���ݒ�
void CCamera::LookAt(CVector3D &eye,CVector3D &at,CVector3D &up){
	m_pos = eye;
	m_at = at;
	m_up = up;
	m_mView.LookAt(eye,at,up);
	m_dir = CVector3D(-m_mView.m20,-m_mView.m21,-m_mView.m22);
}
//�ʒu�Ɖ�]�l�Ńr���[�s���ݒ�
void CCamera::setTranseRot(CVector3D &pos,CVector3D &rot){
	//�J�����̉�]�s����쐬
	CMatrix mRT,mRX,mRY,mRZ,m;
	mRX.RotationX(rot.x);
	mRY.RotationY(rot.y);
	mRZ.RotationZ(rot.z);
	mRT.Transelate(pos.x,pos.y,pos.z);
	m = mRZ*mRY*mRX;
	CVector4D at = m * CVector4D(0,0,1,1);
	LookAt(pos,CVector3D(pos.x+at.x,pos.y+at.y,pos.z+at.z),CVector3D(m.m01,m.m11,m.m21));
}

//���f���s�񂩂�r���[�s���ݒ�
void CCamera::setTranseRot(CMatrix &mtx){
	CVector4D at = mtx * CVector4D(0,0,1,1);
	CVector3D pos = mtx.getTranse();
	LookAt(pos,CVector3D(at.x,at.y,at.z),CVector3D(mtx.m01,mtx.m11,mtx.m21));
}
//�r���[�s��𒼐ڐݒ�
void CCamera::setMatrix(CMatrix &m) {
	m_mView = m;
}
//�r���[�s����擾
CMatrix CCamera::getMatrix(){
	return m_mView;
}
CMatrix CCamera::getBuilbordMatrix(){
	CMatrix m = m_mView;
	m.m03 = m.m13 = m.m23 = 0;
	return m.getInverse();
}
//�J�����̈ʒu���擾
CVector3D CCamera::getPos() {
	return m_pos;
}
//�J�����̌������擾
CVector3D CCamera::getDir() {
	return m_dir;
}