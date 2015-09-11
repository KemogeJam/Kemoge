#include "Utility.h"


void Utility::ScreenToWorld(CVector3D *out,CVector3D spos,CMatrix mProj,CMatrix mView,int w,int h){
	CMatrix	mVP;
	mVP.Viewport(0.0f,0.0f, static_cast<float>(w), static_cast<float>(h));
	CVector4D o = (mView.getInverse() * mProj.getInverse() * mVP.getInverse()) * CVector4D(spos.x,spos.y,spos.z,1);
	*out = CVector3D(o.x/o.w,o.y/o.w,o.z/o.w);
	
}

void Utility::WorldToScreen(CVector3D *out,CVector3D spos,CMatrix mProj,CMatrix mView,int w,int h) {
	CMatrix	mVP;
	mVP.Viewport(0.0f, 0.0f, static_cast<float>(w), static_cast<float>(h));
	CVector4D o = mVP * mProj * mView * CVector4D(spos.x,spos.y,spos.z,1);

	*out =  CVector3D(o.x/o.w,o.y/o.w,1);

}
