#include "CCollision.h"
#include <cmath>

void COBB::Transeform(CMatrix &mtx,bool trans) {
	for (int i=0;i<3;i++) {
		m_axis[i] = mtx * m_axis[i];
	}
	if(trans) {
		CVector4D v = CVector4D(m_base_center.x,m_base_center.y,m_base_center.z,1.0);
		v = mtx * v;
		m_center = CVector3D(v.x,v.y,v.z);
	}
	m_mat = mtx;
}

void COBB::Draw()
{
	glPushMatrix();
	/*
	float f[16] = 
	{
		m_axis[0].x*m_length[0],m_axis[0].y,m_axis[0].z,0,
		m_axis[1].x,m_axis[1].y*m_length[1],m_axis[1].z,0,
		m_axis[2].x,m_axis[2].y,m_axis[2].z*m_length[2],0,
		m_center.x,m_center.y,m_center.z,1
	};
	*/
	SVector3D v[8] = {
		{-m_length[0],m_length[1],m_length[2]},
		{-m_length[0],-m_length[1],m_length[2]},
		{m_length[0],-m_length[1],m_length[2]},
		{m_length[0],m_length[1],m_length[2]},
		{-m_length[0],m_length[1],-m_length[2]},
		{-m_length[0],-m_length[1],-m_length[2]},
		{m_length[0],-m_length[1],-m_length[2]},
		{m_length[0],m_length[1],-m_length[2]},
	};
	int idx[6][4] = {
		{0,1,2,3},
		{4,7,6,5},
		{0,4,5,1},
		{3,2,6,7},
		{0,3,7,4},
		{1,5,6,2},
	};
	glTranslatef(m_center.x,m_center.y,m_center.z);
	glMultMatrixf(CMatrix(m_axis[0].x,m_axis[1].x,m_axis[2].x,0,
						  m_axis[0].y,m_axis[1].y,m_axis[2].y,0,
						  m_axis[0].z,m_axis[1].z,m_axis[2].z,0,
						  0,0,0,1).f
		);
	glBegin(GL_QUADS);
	for(int i=0;i<6;i++) {
		for(int j=0;j<4;j++) {
			glVertex3f(v[idx[i][j]].x,v[idx[i][j]].y,v[idx[i][j]].z);
		}
	}
	glEnd();
	glPopMatrix();
}

bool CCollision::CollisionShpere(const CVector3D &centerA, float radiusA, const CVector3D &centerB, float radiusB) {
	CVector3D v = centerB-centerA;
	return (v.LengthSq() < (radiusA+radiusB)*(radiusA+radiusB));
}
bool CCollision::TriangleIntersect(const CVector3D &c,const CVector3D &v0, const CVector3D &v1,const  CVector3D &v2,const CVector3D &n){

	if(CVector3D::Dot(CVector3D::Cross(v1-v0, c-v0),n)<0) return false;
	if(CVector3D::Dot(CVector3D::Cross(v2-v1, c-v1),n)<0) return false; 
	if(CVector3D::Dot(CVector3D::Cross(v0-v2, c-v2),n)<0) return false;
	return true;
}
//線分と三角形ポリゴンとの衝突判定
bool CCollision::IntersectTriangleRay(CVector3D *corss,const CVector3D &p1, const CVector3D &p2,const CVector3D &v0, const CVector3D &v1, const CVector3D &v2,float *pt ) {
	CVector3D e1, e2,normal,pv1,pv2;

	e1 = v1 - v0;
	e2 = v2 - v0;

	//面の法線を求める
	normal = CVector3D::Cross(e1, e2).GetNormalize();

	//始点からポリゴン上のある地点（どこでもいい）へのベクトル
	pv1 = p1-v0;
	//終点からポリゴン上のある地点（どこでもいい）へのベクトル
	pv2 = p2-v0;

	//ポリゴンの法線との内積を求める
	float d1 = CVector3D::Dot(pv1,normal);
	float d2 = CVector3D::Dot(pv2,normal);

	//ポリゴンを貫通していない
	if(d1*d2>0) return false;

	//始点からポリゴンまでの距離と線分の長さの比率を求める
	//接地地点を出すのに使用する
	float t = d1/(d1-d2);
	if( *pt < t ) return false;

	//裏から貫通している場合は衝突していないことにする
	if(t<0) return false;

	//線分と平面の接地地点を求める
	CVector3D c = p1+(p2-p1)*t;

	//接地地点が三角形ポリゴン上か調べる
	if(!TriangleIntersect(c,v0,v1,v2,normal)) return false;
	
	if(pt) *pt = t;
	if(corss) *corss = c;

	return true;
}

CVector3D CCollision::PointOnLineSegmentNearestPoint(const CVector3D &v0,const CVector3D &v1,const CVector3D &point){
	CVector3D V = v1-v0;
	float a = V.x*V.x+V.y*V.y+V.z*V.z;
	//線分の始点と終点が同じ場所
	if(a==0) return v0;
	CVector3D VP = point-v0;
	float b = CVector3D::Dot(V,VP);
	float t = b/a;
	//v0よりに遠い場合は近い点をV0に
	if(t<0) return v0;
	//V1よりに遠い場合は近い点をV1に
	if(t>1) return v1;
	//t=<1 t>=0 の場合は線分上に近い点がある 
	return v0 + V*t;


}

CVector2D CCollision::PointOnLineSegmentNearestPoint(const CVector2D &v0,const CVector2D &v1,const CVector2D &point){
	CVector2D V = v1-v0;
	float a = V.x*V.x+V.y*V.y;
	//線分の始点と終点が同じ場所
	if(a==0) return v0;
	CVector2D VP = v0-point;
	float b = CVector2D::Dot(V,VP);
	float t = -(b/a);
	//v0よりに遠い場合は近い点をV0に
	if(t<0) return v0;
	//V1よりに遠い場合は近い点をV1に
	if(t>1) return v1;
	//t=<1 t>=0 の場合は線分上に近い点がある 
	return v0 + V*t;


}
//-----------------------------------------------------------------------------
bool CCollision::CollisionTriangleSphere( const CVector3D &v0,const CVector3D &v1,const CVector3D &v2,const CVector3D &center,float radius ,CVector3D *cross,float *length)
{
   
     CVector3D V1(v1-v0);
	 CVector3D V2(v2-v1);
	 CVector3D N(CVector3D::Cross(V1,V2).GetNormalize());
	 
	 CVector3D V = center - v0;
	 //平面と点の距離を求める
	 float Dist = CVector3D::Dot(V,N);
  
	//球の半径より離れている場合は接触無し
	 if(abs(Dist) > radius) return false;

	 //点から平面上に垂直に下ろした地点を求める
	 CVector3D Point =  center - ( N * Dist );
	 
	 
	 //上記の点が三角形ポリゴン内なら接触している
	 if(TriangleIntersect( Point, v0, v1, v2 , N)) {
		if(cross) *cross = Point;
		if(length) *length = Dist;
		return true;
	}



	 //各辺に球がかすっている可能性がある
	 //１辺ごとに球と辺の最短距離を求める

	 //最短距離
	 float l;
	 //最短接触地点
	 CVector3D c;
	 
	 //距離比較用
	 float LengthSq;



	 //辺１(v0→v1)
	 Point = PointOnLineSegmentNearestPoint( v0, v1, center );
	 LengthSq = (center - Point).LengthSq();
	 l  = LengthSq;
	 c = Point;

	 //辺２(v1→v2)
	 Point = PointOnLineSegmentNearestPoint( v1, v2, center );
	 LengthSq = (center - Point).LengthSq();
	 if(l>LengthSq) {
		 l = LengthSq;
		 c = Point;
	 }
	 
	 //辺３(v2→v0)
	 Point = PointOnLineSegmentNearestPoint( v2, v0, center );
	 LengthSq = (center - Point).LengthSq();
	 if(l>LengthSq) {
		 l = LengthSq;
		 c = Point;
	 }


	 l = sqrt(l);
	 //最短距離を確定
	 if(length) *length = l;
	 //最短地点を確定
	 if(cross) *cross = c;
	
    return (l<=radius);
}

bool CCollision::CollisionTriangleCapsule(const CVector3D &v0,const CVector3D &v1,const CVector3D &v2,const CVector3D &top,const CVector3D &bottom,float radius,CVector3D *cross,float *length ){
	
	CVector3D V(top-bottom);

	CVector3D  VP;
	float Dist = 1e10;

	//ポリゴンの法線を求める
	CVector3D N(CVector3D::Cross(v1 - v0, v2 - v0).GetNormalize());

	//始点からポリゴン上のある地点（どこでもいい）へのベクトル
	CVector3D PV1 = top-v0;
	//終点からポリゴン上のある地点（どこでもいい）へのベクトル
	CVector3D PV2 = bottom-v0;

	//ポリゴンの法線との内積を求める
	float d1 = CVector3D::Dot(PV1,N);
	float d2 = CVector3D::Dot(PV2,N);

	if(d1*d2<0) {
		//貫通している場合は線とポリゴンの判定を行う
		if(IntersectTriangleRay(cross,top+CVector3D(0,radius,0),bottom+CVector3D(0,-radius,0),v0,v1,v2,&Dist)) {
			if(length) {
				//貫通点までの距離を求める
				float lt = (*cross - top).LengthSq();
				float lb = (*cross - bottom).LengthSq();
				if(lt<lb) *length = sqrt(lt);
				else *length = sqrt(lb);
			}
			return true;
		}
	}

	d1=abs(d1);
	d2=abs(d2);
	//平面上の点との最短地点を求める
	CVector3D C1(top-N*d1);
	CVector3D C2(bottom-N*d2);
	//点が平面上にない場合は無効、後の辺との接触で調べる
	if(!TriangleIntersect(C1,v0,v1,v2,N)) d1=1e10;
	if(!TriangleIntersect(C2,v0,v1,v2,N)) d2=1e10;


	//面との距離が近い点の距離を選択
	Dist = (d1<d2) ? d1:d2; 
	if(Dist<=radius) {
		//追加
		if(length) *length = Dist;
		return true;
	}
	

	//各辺との距離を求める
	Dist = min(min(DistanceLine(v0,v1,top,bottom),DistanceLine(v1,v2,top,bottom)),DistanceLine(v2,v0,top,bottom));

	if(length) *length = Dist;

    return (Dist<=radius);
	




}
bool CCollision::CompareLength(const COBB &A,const COBB &B,const CVector3D &distVec,const CVector3D &separate,float *length){
	float dist = abs(CVector3D::Dot(distVec,separate));
	float distA = 0;
	for(int i=0;i<3;i++) distA+=abs( CVector3D::Dot(A.m_axis[i],separate)) * A.m_length[i];
	float distB = 0;
	for(int i=0;i<3;i++) distB+=abs( CVector3D::Dot(B.m_axis[i],separate)) * B.m_length[i];
	if(length) *length = abs(dist - (distA+distB)); 
	if(dist > distA + distB) return false;
	return true;
}
bool CCollision::CollisionOBB(const COBB &A,const COBB &B){
	CVector3D distVec = B.m_center - A.m_center;

	for(int i=0;i<3;i++)
		if(!CompareLength(A,B,distVec,A.m_axis[i])) return false;
	
	for(int i=0;i<3;i++)
		if(!CompareLength(A,B,distVec,B.m_axis[i])) return false;
	
	CVector3D separate;
	for(int i=0;i<3;i++) {
		for(int j=0;j<3;j++) {
			separate = CVector3D::Cross(A.m_axis[i],B.m_axis[j]);
			if(!CompareLength(A,B,distVec,separate)) return false;
		}
	}

	return true;
}

bool CCollision::CollisionOBBShpere(const COBB &A,const CVector3D &center , float radius){
	CVector3D V = center-A.m_center;
	CVector3D VL;
	for(int i=0;i<3;i++) {
		VL.v[i] = abs(CVector3D::Dot(A.m_axis[i],V)) - A.m_length[i];
		if(VL.v[i]<0) VL.v[i]=0;
	}
	return (VL.Length()<radius);
	

}
//カプセルと球の衝突判定
bool CCollision::CollisionCapsuleShpere(const CVector3D &c_top,const CVector3D &c_bottom,float c_radius,const CVector3D &s_center , float s_radius){
	float l = DistancePointToLine(c_top,c_bottom,s_center);
	if(l<=c_radius+s_radius) return true;
	return false;
}
//カプセル同士の衝突判定
bool CCollision::CollisionCapsule(const CVector3D &top1,const CVector3D &bottom1,float radius1,const CVector3D &top2,const CVector3D &bottom2,float radius2){
	float l  = DistanceLine(top1,bottom1,top2,bottom2);
	if(l<=radius1+radius2) return true;
	return false;
}
//AABB同士の衝突判定
bool CCollision::CollisionAABB(const CVector3D &minA,const CVector3D &maxA,const CVector3D &minB,const CVector3D &maxB){
	if( minA.x  < maxB.x && maxA.x > minB.x &&
		minA.y  < maxB.y && maxA.y > minB.y &&
		minA.z  < maxB.z && maxA.z > minB.z) return true;
	return false;
}

//2線分間の距離
float CCollision::DistanceLine(const CVector3D &s1,const CVector3D &e1,const CVector3D &s2,const CVector3D &e2,CVector3D *c,CVector3D *c2){

	//線のベクトルを求める
	CVector3D V1(e1-s1);
	CVector3D V2(e2-s2);
	//2つの線分の外積を求める
	CVector3D N(CVector3D::Cross(V1,V2).GetNormalize());
	//2つの線分が平行でない場合
	if (N.LengthSq()) {
		float l = CVector3D::Dot(N, s1-s2);
		CVector3D m = N*l;
		//線分２を線分１と同じ同一平面上に合わせる
		CVector3D S2 = s2+m;
		CVector3D E2 = e2+m;
		//交差しているか調べる
		float d1=CVector3D::Dot(CVector3D::Cross(V1,s1-S2),CVector3D::Cross(V1,s1-E2));
		float d2=CVector3D::Dot(CVector3D::Cross(V2,S2-s1),CVector3D::Cross(V2,S2-e1));
		if( d1 < 0 &&
			 d2 < 0 ) {
				return abs(l);
		}
	}
	//始点と終点から線分との距離を求め、もっとも短い距離を返す
	return sqrt(min(
			min(DistancePointToLineSq(s2, e2, s1),
				DistancePointToLineSq(s2, e2, e1)),
			min(DistancePointToLineSq(s1, e1, s2),
				DistancePointToLineSq(s1, e1, e2))
		));



}
	//点と線の距離
float CCollision::DistancePointToLine(const CVector3D &v0,const CVector3D &v1,const CVector3D &point)
{
	CVector3D p = PointOnLineSegmentNearestPoint(v0,v1,point);
	return (point-p).Length();
}
//点と線の距離
float CCollision::DistancePointToLineSq(const CVector3D &v0,const CVector3D &v1,const CVector3D &point)
{
	CVector3D p = PointOnLineSegmentNearestPoint(v0,v1,point);
	return (point-p).LengthSq();
}
