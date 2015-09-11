#include "CModelX.h"
#include "windows.h"

void CFrameBone::calcBoneMatrix(CMatrix *out) {
	boneMatrix = sMatrix * matrixOffset;

	out[getNo()] = boneMatrix;
}
void CFrameBone::calcMatrix() {
	if (getParent()) sMatrix = ((CFrameBone*)getParent())->getSMatrix() * getMatrix();
	else sMatrix = getMatrix();

	if (getChild()) ((CFrameBone*)getChild())->calcMatrix();
	if (getNext()) ((CFrameBone*)getNext())->calcMatrix();

}
CMaterial::CMaterial(CXMaterial &m) {
	faceColor = m.faceColor;
	power = m.power;
	specularColor = m.specularColor;
	emissiveColor = m.emissiveColor;
	st = CVector2D(0, 0);
	alpha = 1.0f;
	if (strlen(m.filename)) {
		texture = new CTexture();
		if (!texture->Load(m.filename)) {
			delete texture;
			texture = NULL;
		}
	}
	else {
		texture = NULL;
	}
}
CMaterial::~CMaterial() {
	SAFE_DELETE(texture);
}
void CMaterial::set(CShader *shader) {

	int AmbientId = glGetUniformLocation(shader->getProgram(), "Ambient");  //カラー設定
	glUniform4fv(AmbientId, 1, (GLfloat*)&faceColor);

	int DiffuseId = glGetUniformLocation(shader->getProgram(), "Diffuse");  //カラー設定
	glUniform4fv(DiffuseId, 1, (GLfloat*)&faceColor);

	int PowId = glGetUniformLocation(shader->getProgram(), "Pow");  //ライトの向きを設定
	glUniform1f(PowId, power);

	int SpecularId = glGetUniformLocation(shader->getProgram(), "Specular");  //カラー設定
	glUniform3fv(SpecularId, 1, (GLfloat*)&specularColor);


	int EmissiveId = glGetUniformLocation(shader->getProgram(), "Emissive");  //カラー設定
	glUniform3fv(EmissiveId, 1, (GLfloat*)&emissiveColor);
	glUniform1f(glGetUniformLocation(shader->getProgram(), "alpha"), alpha);
	if (texture) {
		glUniform1i(glGetUniformLocation(shader->getProgram(), "usetex"), 1);
		glUniform2fv(glGetUniformLocation(shader->getProgram(), "stscroll"), 1, st.v);
		texture->MapTexture();
	}
	else {
		glUniform1i(glGetUniformLocation(shader->getProgram(), "usetex"), 0);
	}
	GLint samplerId = glGetUniformLocation(shader->getProgram(), "sampler");
	glUniform1i(samplerId, 0);//GL_TEXTURE1を適用

}
void CMaterial::reset() {
	if (texture) {
		texture->UnmapTexture();
	}
}
CSkinWeights::CSkinWeights(CXModelLoader &loader, CXMesh &mesh) {
	weight = new SSkinWeight[mesh.nVertices];
	memset(weight, 0, sizeof(SSkinWeight)*mesh.nVertices);
	std::vector<CXSkinWeights*> *skin = &mesh.skinweights;
	std::vector<CXSkinWeights*>::iterator it = skin->begin();
	while (it != skin->end()) {
		CXSkinWeights* s = *it;
		int bonenum = loader.getFrameNum(s->transformNodeName);
		for (int i = 0; i < s->nWeights; i++) {
			int j;
			for (j = 0; j < 4; j++) {
				if (weight[s->vertexIndices[i]].weight.f[j] == 0.0f) break;
			}
			weight[s->vertexIndices[i]].bone.f[j] = static_cast<float>(bonenum);
			if (j <= 3) weight[s->vertexIndices[i]].weight.f[j] = s->weights[i];

		}
		it++;

	}

}
CSkinWeights::~CSkinWeights() {
	SAFE_DELETE(weight);
}
CPoly::CPoly(CXModelLoader &loader, CXMesh &mesh, CSkinWeights *skinWeights, int matNo) {
	m_pVertex = NULL;


	material = loader.getMaterialNum(mesh.meshMaterialList->material[matNo]);
	faceCnt = 0;
	for (int i = 0; i < mesh.meshMaterialList->nFaceIndexes; i++) {
		if (mesh.meshMaterialList->faceIndexes[i] == matNo) faceCnt++;
	}
	vertexCnt = faceCnt * 3;

	bNormal = (mesh.meshNormal) ? true : false;


	bTexCode = (mesh.meshTextureCoords) ? true : false;

	bWeight = (skinWeights) ? true : false;

	m_pVertex = new MY_VERTEX[vertexCnt];
	for (int i = 0, j = 0; i < mesh.meshMaterialList->nFaceIndexes; i++) {
		if (mesh.meshMaterialList->faceIndexes[i] == matNo) {
			for (int k = 0; k < 3; k++, j++) {
				m_pVertex[j].vPos.x = mesh.vertices[mesh.faces[i].idx[k]].x;
				m_pVertex[j].vPos.y = mesh.vertices[mesh.faces[i].idx[k]].y;
				m_pVertex[j].vPos.z = mesh.vertices[mesh.faces[i].idx[k]].z;
				if (bNormal) {
					m_pVertex[j].vNorm.x = mesh.meshNormal->normals[mesh.meshNormal->faceNormals[i].idx[k]].x;
					m_pVertex[j].vNorm.y = mesh.meshNormal->normals[mesh.meshNormal->faceNormals[i].idx[k]].y;
					m_pVertex[j].vNorm.z = mesh.meshNormal->normals[mesh.meshNormal->faceNormals[i].idx[k]].z;
				}
				if (bTexCode) {
					m_pVertex[j].vTex.x = mesh.meshTextureCoords->textureCoords[mesh.faces[i].idx[k]].u;
					m_pVertex[j].vTex.y = mesh.meshTextureCoords->textureCoords[mesh.faces[i].idx[k]].v;
				}
				if (bWeight) {
					memcpy(m_pVertex[j].bBoneIndex, &skinWeights->weight[mesh.faces[i].idx[k]].bone, sizeof(float) * 4);
					memcpy(m_pVertex[j].bBoneWeight, &skinWeights->weight[mesh.faces[i].idx[k]].weight, sizeof(float) * 4);
				}
			}
		}
	}
	//	printWeight();
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(MY_VERTEX)*vertexCnt, m_pVertex, GL_STATIC_DRAW);
	delete[] m_pVertex;
	m_pVertex = NULL;
	glBindBuffer(GL_ARRAY_BUFFER, 0);



}
CPoly::~CPoly() {
	glDeleteBuffers(1, &buffer);
	SAFE_DELETE_ARRAY(m_pVertex);

}
void CPoly::draw(CShader *shader) {
	int idx = 0;
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(MY_VERTEX), (void*)idx);
	idx += sizeof(SVector3D);
	if (bNormal) {
		glEnableClientState(GL_NORMAL_ARRAY);
		glNormalPointer(GL_FLOAT, sizeof(MY_VERTEX), (void*)idx);
	}
	idx += sizeof(SVector3D);
	if (bTexCode) {
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, sizeof(MY_VERTEX), (void*)idx);
	}
	idx += sizeof(SVector2D);
	if (shader && bWeight) {
		int  weightLoc = glGetAttribLocation(shader->getProgram(), "weights");
		glEnableVertexAttribArray(weightLoc);
		glVertexAttribPointer(weightLoc, 4, GL_FLOAT, GL_TRUE, sizeof(MY_VERTEX), (void*)idx);
		idx += sizeof(float) * 4;
		int  indexLoc = glGetAttribLocation(shader->getProgram(), "indices");
		glEnableVertexAttribArray(indexLoc);
		glVertexAttribPointer(indexLoc, 4, GL_FLOAT, GL_FALSE, sizeof(MY_VERTEX), (void*)idx);
	}
	glDrawArrays(GL_TRIANGLES, 0, vertexCnt);
	glDisableClientState(GL_VERTEX_ARRAY);
	if (bNormal) {
		glDisableClientState(GL_NORMAL_ARRAY);
	}
	if (bTexCode) {
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

CAnimation::CAnimation() {
}
CAnimation::CAnimation(std::vector<CXAnimationSet*> &a) {
	pAnimation = new std::vector < CXAnimationSet* >;
	for (unsigned int i = 0; i < a.size(); i++) {
		pAnimation->push_back(new CXAnimationSet(*a[i]));
	}
	jam = -1;
	pAnimData = NULL;
	pBoneRoot = NULL;
}
CAnimation::~CAnimation() {

}
void CAnimation::Release() {
	if (pAnimation) {
		for (std::vector<CXAnimationSet*>::iterator it = pAnimation->begin(); it != pAnimation->end(); it++) {
			SAFE_DELETE(*it);
		}
		pAnimation->clear();
		delete pAnimation;
		pAnimation = NULL;
	}
}
CMatrix CAnimation::calcMatrix(CXAnimationKey &key, float t) {
	CMatrix m[2], result;
	int i;
	for (i = 0; i < key.nKeys; i++) {
		if (key.keys[i].time >= (int)(t)) break;
	}
	//	if(i==0) return key.keys[0].matrix;

	m[0] = key.keys[i].matrix;
	m[1] = key.keys[i + 1].matrix;
	float r = (float)(key.keys[i + 1].time - (t + 1)) / (key.keys[i + 1].time - key.keys[i].time);

	if (r > 1.0) {
		printf("over");
	}
	result = m[0] * r + m[1] * (1.0f - r);
	return result;

}
void CAnimation::changeAnimation(int j, bool l, bool check, int blendFrame) {
	if (check) {
		if (jam == j) return;
	}
	loop = l;
	jam = j;
	time = 0;
	speed = 1.0f;
	endTime = getEndTime(jam);
	blend = 0.0f;
	blendS = static_cast<float>(1.0 / blendFrame);
	saveBlendMatrix();
}
void CAnimation::saveBlendMatrix() {
	CXAnimationSet* a = (*pAnimation)[jam];
	for (unsigned int i = 0; i < a->animations.size(); i++) {
		CFrameBone *b = (CFrameBone*)CXFrame::getFrameByName(a->animations[i]->boneName, pBoneRoot);
		if (b) {
			b->saveBlendMatrix();
		}

	}
}
void CAnimation::updateMatrix() {
	if (jam == -1 || pBoneRoot == NULL) return;
	CXAnimationSet* a;
	float frame;
	if (pAnimData) {
		a = (*pAnimation)[0];
		frame = time + pAnimData[jam].start;
	}
	else {
		a = (*pAnimation)[jam];
		frame = time;
	}
	for (unsigned int i = 0; i < a->animations.size(); i++) {
		CFrameBone *b = (CFrameBone*)CXFrame::getFrameByName(a->animations[i]->boneName, pBoneRoot);
		if (b) {
			b->setMatrix(calcMatrix(*a->animations[i]->animationkey, frame));
			if (blend < 1.0f) b->calcBlendMatrix(blend);
		}

	}

	//	CXFrame::printMatrix(pBoneRoot);
}
int CAnimation::getEndTime(int j) {
	if (pAnimData) {
		return pAnimData[j].end - pAnimData[j].start;
	}
	if (j >= (int)pAnimation->size()) return -1;
	CXAnimationSet* a = (*pAnimation)[j];
	int e = 0;
	for (unsigned int i = 0; i < a->animations.size(); i++) {
		int m = a->animations[i]->animationkey->keys[a->animations[i]->animationkey->nKeys - 1].time;
		if (e < m) e = m;
	}
	return e;
}
void CAnimation::upDate() {
	time += speed;
	if (time >= endTime - 1.0f) {
		if (loop) {
			time = 0;
		}
		else {
			time = endTime - 1.0f;
		}
	}
	blend += blendS;
	if (blend > 1.0f) blend = 1.0f;
}

CMesh::CMesh(CXModelLoader &loader, CXMesh &mesh, CSkinWeights *bone) {
	matrix = mesh.getMatrix();
	for (int i = 0; i < mesh.meshMaterialList->nMaterials; i++) {
		polyList.push_back(new CPoly(loader, mesh, bone, i));
	}
	if (bone) {
		for (unsigned int i = 0; i < mesh.skinweights.size(); i++) {
			boneList.push_back(new CBoneOffset(*mesh.skinweights[i]));
		}
	}

}
CMesh::~CMesh() {

	for (std::vector<CPoly*>::iterator it = polyList.begin(); it != polyList.end(); it++) {
		SAFE_DELETE(*it);
	}
	polyList.clear();

	for (std::vector<CBoneOffset*>::iterator it = boneList.begin(); it != boneList.end(); it++) {
		SAFE_DELETE(*it);
	}
	boneList.clear();

}
void CMesh::draw(std::vector<CMaterial*> materialList, CShader *shader, CFrameBone *pFrameRoot, CMatrix *boneMatrix, int boneNum) {
	//	glPushMatrix();
	//	glMultMatrixf(matrix.f);
	if (boneList.size() > 0) {
		for (unsigned int i = 0; i < boneList.size(); i++) {
			CFrameBone *b = (CFrameBone*)CXFrame::getFrameByName(boneList[i]->transformNodeName, pFrameRoot);
			b->seMatrixOffset(boneList[i]->matrixOffset);
			b->calcBoneMatrix(boneMatrix);
		}
		if (shader) {
			int MatrixLocation = glGetUniformLocation(shader->getProgram(), "Transforms");
			glUniformMatrix4fv(MatrixLocation, boneNum, GL_FALSE, boneMatrix[0].f);
		}
	}
	//pFrameRoot->calcBoneMatrix();
	CMatrix mat;
	glGetFloatv(GL_MODELVIEW_MATRIX, mat.f);
	std::vector<CPoly*>::iterator it;
	for (it = polyList.begin(); it != polyList.end(); it++) {
		if ((*it)->material != -1) {
			materialList[(*it)->material]->set(shader);
		}
		(*it)->draw(shader);
		if ((*it)->material != -1) {
			materialList[(*it)->material]->reset();
		}

	}
	//	glPopMatrix();
}
CModelX::CModelX() {

}

CModelX::~CModelX() {
	SAFE_DELETE(animation);
}

void CModelX::operator = (const CModelX &m) {
	memcpy(this, &m, sizeof(CModelX));
	animation = new CAnimation();
	memcpy(animation, m.animation, sizeof(CAnimation));
}
void CModelX::Release() {
	for (std::vector<CMesh*>::iterator it = pMeshList->begin(); it != pMeshList->end(); it++) {
		SAFE_DELETE(*it);
	}
	pMeshList->clear();
	SAFE_DELETE(pMeshList);
	for (std::vector<CMaterial*>::iterator it = pMaterialList->begin(); it != pMaterialList->end(); it++) {
		SAFE_DELETE(*it);
	}
	pMaterialList->clear();
	SAFE_DELETE(pMaterialList);
	if (pFrameRoot) pFrameRoot->release();
	pFrameRoot = NULL;
	SAFE_DELETE(boneMatrix);
	if (animation) {
		animation->Release();
	}
	SAFE_DELETE(animation);
	SAFE_DELETE(m_shader);
}
void CModelX::RenderM(CMatrix &m) {

	if (m_shader) {
		m_shader->enable();

		SendShaderParam();
	}
	if (animation) {
		animation->updateMatrix();
		pFrameRoot->calcMatrix();
	}


	glPushMatrix();
	glMultMatrixf(m.f);
	//pFrameRoot->setMatrix(matrix);

	std::vector<CMesh*>::iterator it;
	for (it = pMeshList->begin(); it != pMeshList->end(); it++) {
		(*it)->draw(*pMaterialList, m_shader, pFrameRoot, boneMatrix, boneNum);
	}
	glPopMatrix();
	if (m_shader) m_shader->disable();

}


void CModelX::createFrame(CXFrame *xf, CFrameBone *f, int *num) {
	(*num)++;
	printf("%s %s No%d\n", f->getToken(), f->getName(), f->getNo());
	if (xf->getChild()) {
		CFrameBone *c = new CFrameBone();
		*c = *xf->getChild();
		if (!f->getChild()) f->setChild(c);
		c->setParent(f);
		createFrame(xf->getChild(), c, num);
	}
	if (xf->getNext()) {
		CFrameBone *c = new CFrameBone();
		*c = *xf->getNext();
		f->setNext(c);
		c->setPrev(f);
		c->setParent(f->getParent());
		createFrame(xf->getNext(), c, num);
	}
}
bool CModelX::Load(CXModelLoader &loader) {
	boneNum = 0;
	//	printf("f\n");
	//	CXFrame::printFrame(pFrameRoot,0);

	if (0 < loader.animationset.size()) {

		pFrameRoot = new CFrameBone();
		*pFrameRoot = *loader.pRoot;
		createFrame(loader.pRoot, pFrameRoot, &boneNum);
		boneMatrix = new CMatrix[boneNum];

		animation = new CAnimation(loader.animationset);
		animation->attachFrame(pFrameRoot);
		//		CXFrame::printMatrix(pFrameRoot);



				//アニメーション用
		m_shader = new CShader("shader\\skinmesh.vert", "shader\\mesh.flag");
	}
	else {
		animation = NULL;
		//アニメーション無し用
		m_shader = new CShader("shader\\mesh.vert", "shader\\mesh.flag");
	}
	pMaterialList = new std::vector<CMaterial*>;
	for (unsigned int i = 0; i < loader.materials.size(); i++)
		pMaterialList->push_back(new CMaterial(*loader.materials[i]));

	pMeshList = new std::vector < CMesh* >;
	for (unsigned int i = 0; i < loader.mesh.size(); i++) {
		CXMesh *m = loader.mesh[i];
		CSkinWeights *weight = NULL;
		if (m->nFaces == 0) continue;
		if (0 < loader.animationset.size()) {
			if (m->skinweights.size() > 0) {
				weight = new CSkinWeights(loader, *m);
			}
		}
		if (0 < loader.animationset.size()) {
			for (unsigned int j = 0; j < m->skinweights.size(); j++) {
				CFrameBone *f = (CFrameBone*)CXFrame::getFrameByName(m->skinweights[j]->transformNodeName, pFrameRoot);
				f->seMatrixOffset(m->skinweights[j]->matrixOffset);
			}
		}
		pMeshList->push_back(new CMesh(loader, *m, weight));
		if (m->skinweights.size() > 0) {
			delete weight;
		}
	}
	return true;

}
bool CModelX::Load(const char* filePath) {
	CXModelLoader loader(filePath);
	return Load(loader);

}

void CModelX::UpdateAnimation() {
	if (animation) {
		animation->upDate();
	}
}

CMatrix CModelX::getFrameMatrix(const char *name, bool local) {
	CFrameBone *f = (CFrameBone*)CFrameBone::getFrameByName(name, pFrameRoot);
	return (local) ? f->getSMatrix() : getMatrix() * f->getSMatrix();
}
CMatrix CModelX::getFrameMatrix(int no, bool local) {
	CFrameBone *f = (CFrameBone*)CFrameBone::getFrameByNo(no, pFrameRoot);
	return (local) ? f->getSMatrix() : getMatrix() * f->getSMatrix();
}