#include "CModelSX.h"

CSPoly::~CSPoly(){
	delete[] m_vertex;
	delete[] m_normal;
	delete[] m_texCoord;
}
void CSPoly::create(CXSModelLoader &loader,int materialNo){
	
	m_vertexCnt = 0;
	for(int i=0;i<loader.m_faceNum;i++) {
		if(loader.m_materialList[i] == materialNo) m_vertexCnt++;
	}
	m_vertexCnt*=3;
	m_vertex = new CVector3D[m_vertexCnt];
	if (loader.m_normal)
		m_normal = new CVector3D[m_vertexCnt];
	else
		m_normal = NULL;
	if(loader.m_texCoord) 
		m_texCoord = new CXSTexCoord[m_vertexCnt];
	else 
		m_texCoord = NULL;
	CVector3D *v = m_vertex;
	CVector3D *n = m_normal;
	CXSTexCoord *t = m_texCoord;
	for(int i=0;i<loader.m_faceNum;i++) {
		if(loader.m_materialList[i] != materialNo) continue;
		for(int j=0;j<3;j++) {
			v[j].x = loader.m_vertex[loader.m_vertexIndex[i*3+j]].x;
			v[j].y = loader.m_vertex[loader.m_vertexIndex[i*3+j]].y;
			v[j].z = loader.m_vertex[loader.m_vertexIndex[i*3+j]].z;
		}
		v+=3;
		if(n) {
			for(int j=0;j<3;j++) {
				n[j].x = loader.m_normal[loader.m_normalIndex[i*3+j]].x;
				n[j].y = loader.m_normal[loader.m_normalIndex[i*3+j]].y;
				n[j].z = loader.m_normal[loader.m_normalIndex[i*3+j]].z;
			}
			n+=3;
		}
		if(t) {
			for(int j=0;j<3;j++) {
				t[j].u = loader.m_texCoord[loader.m_vertexIndex[i*3+j]].u;
				t[j].v = loader.m_texCoord[loader.m_vertexIndex[i*3+j]].v;
			}
			t+=3;
		}
		
	}

}
void CSPoly::draw(){
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,m_vertex);
	if(m_normal) {
		glEnableClientState(GL_NORMAL_ARRAY);
		glNormalPointer(GL_FLOAT,0,m_normal);
	}
	if(m_texCoord) {
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2,GL_FLOAT,0,m_texCoord);
	}
	glDrawArrays(GL_TRIANGLES,0,m_vertexCnt);
	glDisableClientState(GL_VERTEX_ARRAY);
	if(m_normal) { 
		glDisableClientState(GL_NORMAL_ARRAY);
	}
	if(m_texCoord) {
		glDisableClientState(GL_TEXTURE_COORD_ARRAY); 
	}
	
}
CSCollPoly::CSCollPoly(CXSModelLoader &loader,int cut) {
	m_vertex = new CVector3D[loader.m_vertexNum];
	memcpy(m_vertex,loader.m_vertex,sizeof(CVector3D)*loader.m_vertexNum);
	m_normal = new CVector3D[loader.m_normalNum];
	memcpy(m_normal,loader.m_normal,sizeof(CVector3D)*loader.m_normalNum);
	m_triData = new STriangle[loader.m_faceNum];
	for(int i=0;i<loader.m_faceNum;i++) {
		m_triData[i].set(&loader.m_vertexIndex[i*3],&loader.m_normalIndex[i*3],loader.m_materialList[i]);
	}
	m_tri = new CSCollBase;
	for(int i=0;i<loader.m_faceNum;i++) {
		m_tri->add(&m_triData[i]);
	}
}
CSCollPoly::~CSCollPoly() {
	delete[] m_vertex;
	delete[] m_normal;
	delete m_tri;
	delete[] m_triData;
}

bool CSCollPoly::rayTest(CVector3D *c,CVector3D *n,CVector3D s,CVector3D e){
	return m_tri->rayTest(c,n,s,e,m_vertex,m_normal);
		
}
bool CSCollPoly::sphereTest(CVector3D *c,CVector3D *n,float *length,CVector3D center,float radius){
	return m_tri->sphereTest(c,n,length,center,radius,m_vertex,m_normal);
		
}
int CSCollPoly::sphereTest(CCollTriangle *out,CVector3D center,float radius){
	return m_tri->sphereTest(out,center,radius,m_vertex,m_normal);
		
}
int CSCollPoly::cupselTest(CCollTriangle *out,CVector3D top,CVector3D bottom,float radius){
	return m_tri->cupselTest(out,top,bottom,radius,m_vertex,m_normal);
		
}
CModelSX::CModelSX() : m_poly(NULL),m_coll(NULL),m_material(NULL){
}

CModelSX::~CModelSX() {
}
void CModelSX::Release() {
	delete[] m_poly;
	delete m_coll;
	delete[] m_material;
	delete m_shader;

}
bool CModelSX::Load(const char *filePath,int mode){
	CXSModelLoader loader(filePath);
	m_material = new SSModelMaterial[loader.m_materialNum];
	m_materialNum = loader.m_materialNum;
	if(mode & CMODEL_MODE_DRAW) {
		m_poly = new CSPoly[m_materialNum];
		for(int i=0;i<m_materialNum;i++) {
			SSModelMaterial *m = &m_material[i];
			m->faceColor = loader.m_material[i].faceColor;
			m->power = loader.m_material[i].power;
			m->emissiveColor = loader.m_material[i].emissiveColor;
			m->specularColor = loader.m_material[i].specularColor;
			m->alpha = 1.0f;
			if(loader.m_material[i].filePath[0]) {
				m->texture = new CTexture();
				m->texture->Load(loader.m_material[i].filePath);
			}
			m_poly[i].create(loader,i);
		}
		m_shader = new CShader("shader\\mesh.vert","shader\\mesh.flag");
	}
	if(mode & CMODEL_MODE_COLLISION) {
		m_coll = new CSCollPoly(loader,0);
	}
	m_mode = mode;
	return true;
}
void CModelSX::RenderM(CMatrix &m){
	if(!(m_mode & CMODEL_MODE_DRAW)) return;
	m_shader->enable();


	SendShaderParam();

	glPushMatrix();
	glMultMatrixf(m.f);

	for(int i=0;i<m_materialNum;i++) {
		SSModelMaterial *m = &m_material[i];
		int AmbientId = glGetUniformLocation(m_shader->getProgram(),"Ambient");  //ライトの向きを設定
		glUniform4fv(AmbientId,1,(GLfloat*)&m->faceColor);
		
		int DiffuseId = glGetUniformLocation(m_shader->getProgram(),"Diffuse");  //ライトの向きを設定
		glUniform4fv(DiffuseId,1,(GLfloat*)&m->faceColor);
		
		int PowId = glGetUniformLocation(m_shader->getProgram(),"Pow");  //ライトの向きを設定
		glUniform1f(PowId,m->power);
				
		int SpecularId = glGetUniformLocation(m_shader->getProgram(),"Specular");  //ライトの向きを設定
		glUniform3fv(SpecularId,1,(GLfloat*)&m->specularColor);

		
		int EmissiveId = glGetUniformLocation(m_shader->getProgram(),"Emissive");  //ライトの向きを設定
		glUniform3fv(EmissiveId,1,(GLfloat*)&m->emissiveColor);

		
		glUniform1f(glGetUniformLocation(m_shader->getProgram(),"alpha"),m->alpha);

		if(m->texture) {
			glUniform1i(glGetUniformLocation(m_shader->getProgram(),"usetex"),1);
			glUniform2fv(glGetUniformLocation(m_shader->getProgram(),"stscroll"),1,m->st.v);
			m->texture->MapTexture();
		} else {
			glUniform1i(glGetUniformLocation(m_shader->getProgram(),"usetex"),0);
		}
		GLint samplerId = glGetUniformLocation(m_shader->getProgram(), "sampler");
		glUniform1i(samplerId, 0);//GL_TEXTURE1を適用

		//glUniform1i(glGetUniformLocation(m_shader->getProgram(), "sampler7"), 7);//GL_TEXTURE7を適用
	  

		m_poly[i].draw();
		if(m->texture) {
			m->texture->UnmapTexture();
		}
	}
	m_shader->disable();
	glPopMatrix();

}

bool CModelSX::CollisionRay(CVector3D *c,CVector3D *n,CVector3D s,CVector3D e){
	if(m_coll) {
		CMatrix inv = m_matrix.getInverse();
		CVector4D s2 = CVector4D(s.x,s.y,s.z,1);
		s2 = s2*inv;
		CVector4D e2 = CVector4D(e.x,e.y,e.z,1);
		e2 = e2*inv;
	
		if(m_coll->rayTest(c,n,CVector3D(s2.x,s2.y,s2.z),CVector3D(e2.x,e2.y,e2.z))) {
			CVector4D c2 = CVector4D(c->x,c->y,c->z,1);
			c2 = c2*m_matrix;
			*c = CVector3D(c2.x,c2.y,c2.z);
			return true;
		}	
	}
	return false;
		
}

bool CModelSX::CollisionSphere(CVector3D *c,CVector3D *n,float *length,CVector3D center,float radius){
	float scale = CVector3D (m_matrix.m00,m_matrix.m10,m_matrix.m20).Length();
	radius = radius / scale;
	CVector4D center2 = CVector4D(center.x,center.y,center.z,1);
	center2 = center2*m_matrix.getInverse();
	if(m_coll) {
		if(m_coll->sphereTest(c,n,length,CVector3D(center2.x,center2.y,center2.z),radius)) {
			CVector4D cross = CVector4D(c->x,c->y,c->z,1);
			cross = cross * m_matrix;
			*n = *n * m_matrix;
			n->Normalize();
			*c = CVector3D(cross.x,cross.y,cross.z);
			*length = *length*scale;
			return true;
		}	
	}
	return false;
		
}
int CModelSX::CollisionSphere(CCollTriangle *out,CVector3D center,float radius){
	float scale = CVector3D (m_matrix.m00,m_matrix.m10,m_matrix.m20).Length();
	radius = radius / scale;
	CVector4D center2 = CVector4D(center.x,center.y,center.z,1);
	center2 = center2*m_matrix.getInverse();
	if(m_coll) {
		int n = m_coll->sphereTest(out,CVector3D(center2.x,center2.y,center2.z),radius);
		for(int i=0;i<n;i++) {
			out[i].m_normal = out[i].m_normal * m_matrix;
			out[i].m_normal.Normalize();
			out[i].m_dist = out[i].m_dist * scale;
		}
		return n;
	}
	return 0;
		
}
int CModelSX::CollisionCupsel(CCollTriangle *out,CVector3D top,CVector3D bottom,float radius){
	float scale = CVector3D (m_matrix.m00,m_matrix.m10,m_matrix.m20).Length();
	radius = radius / scale;
	top = top*m_matrix.getInverse();
	bottom = bottom*m_matrix.getInverse();
	if(m_coll) {
		int n = m_coll->cupselTest(out,top,bottom,radius);
		for(int i=0;i<n;i++) {
			out[i].m_normal = out[i].m_normal * m_matrix;
			out[i].m_normal.Normalize();
			out[i].m_dist = out[i].m_dist * scale;
		}
		return n;
	}
	return 0;
		
}