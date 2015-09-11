#include "CCamera.h"

CCamera CCamera::m_camera[5];
CCamera* CCamera::m_pCurrent = &m_camera[0];


//カメラオブジェクトを取得
CCamera* CCamera::getCamera(int num) {
	return &m_camera[num];
}
//カメラオブジェクトを取得
CCamera* CCamera::getCurrent() {
	return m_pCurrent;
}
//カメラオブジェクトを取得
void CCamera::setCurrent(int num) {
	m_pCurrent = &m_camera[num];
}
//カメラオブジェクトを取得
void CCamera::setCurrent(CCamera *p) {
	m_pCurrent = p;
}
//コンストラクタ
CCamera::CCamera(){
}
//幅を取得
float CCamera::getWhidth() {
	return m_whidth;
}
//高さを取得
float CCamera::getHeight() {
	return m_height;
}
//幅と高さを設定
void CCamera::SetSize(float w,float h) {
	m_whidth = w;
	m_height = h;
}
//注視カメラでビュー行列を設定
void CCamera::LookAt(CVector3D &eye,CVector3D &at,CVector3D &up){
	m_pos = eye;
	m_at = at;
	m_up = up;
	m_mView.LookAt(eye,at,up);
	m_dir = CVector3D(-m_mView.m20,-m_mView.m21,-m_mView.m22);
}
//位置と回転値でビュー行列を設定
void CCamera::setTranseRot(CVector3D &pos,CVector3D &rot){
	//カメラの回転行列を作成
	CMatrix mRT,mRX,mRY,mRZ,m;
	mRX.RotationX(rot.x);
	mRY.RotationY(rot.y);
	mRZ.RotationZ(rot.z);
	mRT.Transelate(pos.x,pos.y,pos.z);
	m = mRZ*mRY*mRX;
	CVector4D at = m * CVector4D(0,0,1,1);
	LookAt(pos,CVector3D(pos.x+at.x,pos.y+at.y,pos.z+at.z),CVector3D(m.m01,m.m11,m.m21));
}

//モデル行列からビュー行列を設定
void CCamera::setTranseRot(CMatrix &mtx){
	CVector4D at = mtx * CVector4D(0,0,1,1);
	CVector3D pos = mtx.getTranse();
	LookAt(pos,CVector3D(at.x,at.y,at.z),CVector3D(mtx.m01,mtx.m11,mtx.m21));
}
//ビュー行列を直接設定
void CCamera::setMatrix(CMatrix &m) {
	m_mView = m;
}
//ビュー行列を取得
CMatrix CCamera::getMatrix(){
	return m_mView;
}
CMatrix CCamera::getBuilbordMatrix(){
	CMatrix m = m_mView;
	m.m03 = m.m13 = m.m23 = 0;
	return m.getInverse();
}
//カメラの位置を取得
CVector3D CCamera::getPos() {
	return m_pos;
}
//カメラの向きを取得
CVector3D CCamera::getDir() {
	return m_dir;
}