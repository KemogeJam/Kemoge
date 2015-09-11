/*!
*	@brief	X�t�@�C���i�X�^�e�B�b�N���f���j�p���f���N���X
*
*
**/


#pragma once
#include "CXSModelLoader.h"
#include "CModel.h"
#include "CTexture.h"
#include "CShader.h"
#include "CCollision.h"

struct SSModelMaterial{
	CXSColorRGBA faceColor;
	float power;
	CXSColorRGB specularColor;
	CXSColorRGB emissiveColor;
	CVector2D	st;
	CTexture	*texture;
	float		alpha;
	SSModelMaterial() : st(0,0){
		texture = NULL;
	}
	~SSModelMaterial() {
		delete texture;
	}

};
class CSPoly {
	CVector3D *m_vertex;
	int			m_vertexCnt;
	CVector3D *m_normal;
	CXSTexCoord *m_texCoord;
public:
	~CSPoly();
	void create(CXSModelLoader &loader,int materialNo);
	void draw();

};
#define POLY_CUT 5

class CCollTriangle {
public:
	CVector3D	m_normal;
	float	m_dist;
};
struct STriangle{
	int	idxv[3];
	int	idxn[3];
	int	mat;
	STriangle(){
	}
	STriangle(int *v,int *n,int m) {
		set(v,n,m);
	}
	void set(int *v,int *n,int m){
		for(int i=0;i<3;i++) {
			idxv[i] = v[i];
			idxn[i] = n[i];
		}
		mat = m;
	}
	
	CVector3D getNormal(CVector3D *vertex) {
		CVector3D e1 = vertex[idxv[1]] - vertex[idxv[0]];
		CVector3D e2 = vertex[idxv[2]] - vertex[idxv[0]];

		return	CVector3D::Cross(e1, e2).GetNormalize();
	}
	bool rayTest(CVector3D *c,CVector3D p1,CVector3D p2,CVector3D *vertex,CVector3D *normal,float *t) {
		return CCollision::IntersectTriangleRay(c,p1,p2,vertex[idxv[0]],vertex[idxv[1]],vertex[idxv[2]],t);
	}
	bool sphereTest(CVector3D *c,float *length,CVector3D center,float raduis,CVector3D *vertex) {
		return CCollision::CollisionTriangleSphere(vertex[idxv[0]],vertex[idxv[1]],vertex[idxv[2]],center,raduis,c,length);
	}
	bool cupselTest(CVector3D *c,float *length,CVector3D top,CVector3D bottom,float raduis,CVector3D *vertex) {
		return CCollision::CollisionTriangleCapsule(vertex[idxv[0]],vertex[idxv[1]],vertex[idxv[2]],top,bottom,raduis,c,length);
	}
};
struct STriangleList {
	STriangle *m_tri;
	STriangleList *m_next;
	STriangleList() {
		m_next = NULL;
	}
	STriangleList(STriangle *t) {
		m_tri = t;
		m_next = NULL;
	}

};
class CSCollBase{
	STriangleList	*m_Top;
	STriangleList	*m_Current;
public:
	CSCollBase(){
		m_Top = NULL;
		m_Current = NULL;
	}
	~CSCollBase(){
		STriangleList *t=m_Top;
		while(t) {
			STriangleList *t2 = t->m_next;
			delete t;
			t = t2;
		}
	}
	void add(STriangle *data) {
		STriangleList *t = new STriangleList(data);
		if(!m_Top) m_Top = t;
		if(m_Current) m_Current->m_next=t;
		m_Current = t;
	}
	bool rayTest(CVector3D *c,CVector3D *n,CVector3D p1,CVector3D p2,CVector3D *vertex,CVector3D *normal) {
		STriangleList *t=m_Top;
		STriangleList *hit=NULL;
		bool result = false;
		float lenge = 1e10;
		float l = 1e10;
		while(t) {
			if(t->m_tri->rayTest(c,p1,p2,vertex,normal,&l)) {
				if(l<lenge) {
					lenge = l;
					hit = t;
				}
			}
			t = t->m_next;
		}
		CVector3D v = p2-p1;
		if(hit) {
			*c = p1 + v*lenge;
			*n = hit->m_tri->getNormal(vertex);
			
		}
		return hit != 0;
	}
	bool sphereTest(CVector3D *cross,CVector3D *c_normal,float *length,CVector3D center,float radius,CVector3D *vertex,CVector3D *normal) {
		STriangleList *t=m_Top;
		bool result = false;
		CVector3D c;
		float l = 1e10;
		*length = l;
		
		while(t) {
			if(t->m_tri->sphereTest(&c,&l,center,radius,vertex)) {
				
				result = true;
				if(l < *length) {
					*length=l;
					*cross = c;
					*c_normal = normal[t->m_tri->idxn[0]];
				}
			}
			t = t->m_next;
		}
		return result;
	}
	int sphereTest(CCollTriangle *out,CVector3D center,float radius,CVector3D *vertex,CVector3D *normal) {
		STriangleList *t=m_Top;
		int num = 0;
		CVector3D c;
		float l;

		while(t) {
			if(t->m_tri->sphereTest(&c,&l,center,radius,vertex)) {
				
				out[num].m_normal = normal[t->m_tri->idxn[0]];
				out[num].m_dist = l;
				num++;
			}
			t = t->m_next;
		}
		return num;
	}
	int cupselTest(CCollTriangle *out,CVector3D top,CVector3D bottom,float radius,CVector3D *vertex,CVector3D *normal) {
		STriangleList *t=m_Top;
		int num = 0;
		CVector3D c;
		float l;

		while(t) {
			if(t->m_tri->cupselTest(&c,&l,top,bottom,radius,vertex)) {
				out[num].m_normal = normal[t->m_tri->idxn[0]];
				out[num].m_dist = l;
				num++;
			}
			t = t->m_next;
		}
		return num;
	}

};
class CSCollPoly {
	STriangle *m_triData;
	CVector3D *m_vertex;
	CVector3D *m_normal;
	CSCollBase *m_tri;
public:
	CSCollPoly(CXSModelLoader &loader,int cut);
	~CSCollPoly();
	bool rayTest(CVector3D *c,CVector3D *n,CVector3D s,CVector3D e);
	bool sphereTest(CVector3D *c,CVector3D *c_n,float *length,CVector3D center,float radius);
	int	sphereTest(CCollTriangle *out,CVector3D center,float radius);
	int	cupselTest(CCollTriangle *out,CVector3D top,CVector3D bottom,float radius);
	//void draw();

};
//�`��p
#define CMODEL_MODE_DRAW (1<<0)
//����p
#define CMODEL_MODE_COLLISION (1<<1)
/*!
	@brief�@X�t�@�C���p���f���N���X
**/
class CModelSX : public CModel{
private:
	CSPoly		*m_poly;
	CSCollPoly	*m_coll;
	SSModelMaterial *m_material;
	int			m_materialNum;
	int			m_mode;
public:
	/*!
		@brief	�R���X�g���N�^

	**/
	CModelSX();
	/*!
		@brief	�f�X�g���N�^
				�f�[�^�̔j���͂��Ȃ�
	**/
	~CModelSX();
	/*!
		@brief	���f���̓ǂݍ���
		@param	path			[in] �t�@�C����
		@retval	true:�����@false:���s
	**/
	bool Load(const char *path) {
		return Load(path,CMODEL_MODE_DRAW);
	}
	
	/*!
		@brief	���[�h���w�肵�ēǂݍ���
		@param	mode			[in] �`��p�A����p�A���p�̃t���O���Z�b�g
		@retval true:�����@false:���s
	**/
	bool Load(const char *filePath,int mode);
	
	/*!
		@brief	�s����w�肵�ĕ`�悷��
		@param	m				[in] ���[���h�s��
		@retval	����
	**/
	void RenderM(CMatrix &m);
	
	/*!
		@brief	���f���f�[�^��j������
		@retval	����
	**/
	void Release();

	/*!
		@brief	�����ƃ��f���̔���
		@param	c				[out] �ڐG�n�_
		@param	s				[in] �����̊J�n�n�_
		@param	e				[in] �����̏I���n�_
		@retval	true:�ڐG�@false:��ڐG
	**/
	bool CollisionRay(CVector3D *c,CVector3D *n,CVector3D s,CVector3D e);
	
	/*!
		@brief	���ƃ��f���̔���
		@param	c				[out] �ڐG�ŒZ�n�_
		@param	n				[out] �ڐG�|���S���̖@��
		@param	center			[in] ���̒��S
		@param	radius			[in] ���̔��a
		@retval	true:�ڐG�@false:��ڐG
	**/
	bool CollisionSphere(CVector3D *c,CVector3D *n,float *length,CVector3D center,float radius);


	/*!
		@brief	���ƃ��f���̔���
		@param	out				[out] �ڐG�f�[�^
		@param	center			[in] ���̒��S
		@param	radius			[in] ���̔��a
		@retval	�ڐG�|���S����
	**/
	int CollisionSphere(CCollTriangle *out,CVector3D center,float radius);

	
	
	/*!
		@brief	�J�v�Z���ƃ��f���̔���
		@param	out				[out] �ڐG�f�[�^
		@param	top				[in] �J�v�Z���̓V��
		@param	bottom			[in] �J�v�Z���̒�
		@param	radius			[in] ���̔��a
		@retval	�ڐG�|���S����
	**/
	int CollisionCupsel(CCollTriangle *out,CVector3D top,CVector3D bottom,float radius);
	
	void setAlpha(int no,float alpha) {
		m_material[no].alpha = alpha;
	}
	
	SSModelMaterial *getMaterial(int no){
		return &m_material[no];
	}
};