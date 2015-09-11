#include "CModelObj.h"
#include <string.h>

CMaterialObj::CMaterialObj() : m_pTex(NULL),m_alpha(1.0),m_st(0,0){
}
void CMaterialObj::Map(CShader *shader) {


	int AmbientId = glGetUniformLocation(shader->getProgram(),"Ambient");  //カラー設定
	glUniform4fv(AmbientId,1,m_ambient);
	
	int DiffuseId = glGetUniformLocation(shader->getProgram(),"Diffuse");  //カラー設定
	glUniform4fv(DiffuseId,1,m_diffuse);
	
	int PowId = glGetUniformLocation(shader->getProgram(),"Pow");  //ライトの向きを設定
	glUniform1f(PowId,m_shininess);
			
	int SpecularId = glGetUniformLocation(shader->getProgram(),"Specular");  //カラー設定
	glUniform3fv(SpecularId,1,m_specular);

	float em[4]={0,0,0,0};
	int EmissiveId = glGetUniformLocation(shader->getProgram(),"Emissive");  //カラー設定
	glUniform3fv(EmissiveId,1,em);
	
	glUniform1f(glGetUniformLocation(shader->getProgram(),"alpha"),m_alpha);
	
	if(m_pTex) {
		glUniform1i(glGetUniformLocation(shader->getProgram(),"usetex"),1);
		glUniform2fv(glGetUniformLocation(shader->getProgram(),"stscroll"),1,m_st.v);
		m_pTex->MapTexture();
	} else {
		glUniform1i(glGetUniformLocation(shader->getProgram(),"usetex"),0);
	}
	GLint samplerId = glGetUniformLocation(shader->getProgram(), "sampler");
	glUniform1i(samplerId, 0);//GL_TEXTURE1を適用
}

void CMaterialObj::Unmap() {
	if(m_pTex) {
		m_pTex->UnmapTexture();
	}
}

void CMaterialObj::Release() {
	if(m_pTex) {m_pTex->Release();m_pTex=NULL;}
}

CMeshObj::CMeshObj() : m_pVertexAry(NULL),m_pNormalAry(NULL),m_pTexCoordAry(NULL),m_vertexNum(0){
}
void CMeshObj::Render(CShader *shader) {
	m_material.Map(shader);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, m_buffers[0]);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_buffers[1]);
	glNormalPointer(GL_FLOAT, 0, m_pNormalAry);
	glBindBuffer(GL_ARRAY_BUFFER, m_buffers[2]);
	glTexCoordPointer(2,GL_FLOAT,0,m_pTexCoordAry);

	glDrawArrays(GL_TRIANGLES,0,m_vertexNum);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	m_material.Unmap();
}
void CMeshObj::Release() {
	
//	if(m_pVertexAry)  {delete[] m_pVertexAry; m_pVertexAry=NULL;}
//	if(m_pNormalAry)  {delete[] m_pNormalAry; m_pNormalAry=NULL;}
//	if(m_pTexCoordAry)  {delete[] m_pTexCoordAry; m_pTexCoordAry=NULL;}
	glDeleteBuffers(3, m_buffers);
	m_material.Release();
}

void CMeshObj::SendBuffer(){
	glGenBuffers(3, m_buffers);
	glBindBuffer(GL_ARRAY_BUFFER, m_buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(CVector3D)*m_vertexNum, m_pVertexAry, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(CVector3D)*m_vertexNum, m_pNormalAry, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_buffers[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(CVector2D)*m_vertexNum, m_pTexCoordAry, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	if(m_pVertexAry)  {delete[] m_pVertexAry; m_pVertexAry=NULL;}
	if(m_pNormalAry)  {delete[] m_pNormalAry; m_pNormalAry=NULL;}
	if(m_pTexCoordAry)  {delete[] m_pTexCoordAry; m_pTexCoordAry=NULL;}

	
}
bool CModelObj::LoadMaterial(char *path) {
	char key[32];
	FILE* fp;
	fopen_s(&fp,path,"r");
	//ファイルが開けなかった場合はエラーを表示しfalseを返す
	if(fp==NULL) {
		printf("ファイルがありません%s\n",path);
		return false;
	}

	m_materialCnt = 0;
	while(!feof(fp)) {
		fscanf_s(fp,"%s",key,32);
		if(strcmp(key,"newmtl")==0)
			m_materialCnt++;
	}
	m_mesh = new CMeshObj[m_materialCnt];
	m_materialCnt=0;
	CMeshObj *m = m_mesh;
	fseek(fp,0,SEEK_SET);
	while(!feof(fp)) {
		fscanf_s(fp,"%s",key,32);
		if(strcmp(key,"newmtl")==0) {
			m = &m_mesh[m_materialCnt];
			char name[32];
			fscanf_s(fp,"%s",name,32);
			strcpy_s(m->m_materialname,32,name);

			m_materialCnt++;
		}
		if(strcmp(key,"Ka")==0) {
			fscanf_s(fp,"%f %f %f",&m->m_material.m_ambient[0],&m->m_material.m_ambient[1],&m->m_material.m_ambient[2]);
			m->m_material.m_ambient[3] = 1.0f;
		} else 
		if(strcmp(key,"Kd")==0) {
			fscanf_s(fp,"%f %f %f",&m->m_material.m_diffuse[0],&m->m_material.m_diffuse[1],&m->m_material.m_diffuse[2]);
			m->m_material.m_diffuse[3] = 1.0f;
		} else 
		if(strcmp(key,"Ks")==0) {
			fscanf_s(fp,"%f %f %f",&m->m_material.m_specular[0],&m->m_material.m_specular[1],&m->m_material.m_specular[2]);
			m->m_material.m_specular[3] = 1.0f;
		}else
		if(strcmp(key,"Ns")==0) {
			fscanf_s(fp,"%f",&m->m_material.m_shininess);
		} else 
		if(strcmp(key,"d")==0) {
			float aplha;
			fscanf_s(fp,"%f",&aplha);
			m->m_material.m_ambient[3] = aplha;
			m->m_material.m_diffuse[3] = aplha;
			m->m_material.m_specular[3] = aplha;
		} else
		if(strcmp(key,"map_Kd")==0) {
			char str[32];
			fscanf_s(fp,"%s",str,32);
			m->m_material.m_pTex = new CTexture();
			m->m_material.m_pTex->Load(str);
		}
			
	}
	return true;
}

CModelObj::CModelObj(){
}
CModelObj::~CModelObj() {
}
bool CModelObj::Load(const char *path) {
	//ファイルポインタ(fp)の作成し開いたファイルのハンドルを渡す。
	FILE* fp;
	fopen_s(&fp,path,"r");
	//ファイルが開けなかった場合はエラーを表示しfalseを返す
	if(fp==NULL) {
		printf("ファイルがありません%s\n",path);
		return false;
	}
	//座標データ用カウンター
	int	VCnt=0;
	//法線データ用カウンター
	int	NCnt=0;
	//テクスチャーコード用カウンター
	int	TCnt=0;
	//面データ用カウンター
	int	FCnt=0;
	//キーワード格納用
	char key[32];
	//ファイルの末尾でなければ繰り返す
	CMeshObj *m=NULL;
	while(!feof(fp)) {
		//keyをクリア
		key[0]=0;
		//1単語　文字列を読み込み
		fscanf_s(fp,"%s",key,32);
		//読み込んだキーワードが「v」なら座標データカウンターをカウントアップ
		if(strcmp(key,"v")==0) {
			VCnt++;
		} else 
		if(strcmp(key,"usemtl")==0) {
			char name[32];
			fscanf_s(fp,"%s",name,32);
			for(int i=0;i<m_materialCnt;i++) {
				if(strcmp(name,m_mesh[i].m_materialname)==0) {
					m = &m_mesh[i];
				}
			}
		}
		//読み込んだキーワードが「f」なら面データカウンターをカウントアップ
		if(strcmp(key,"f")==0) {
			//頂点数をカウントアップ
			if(m) m->m_vertexNum+=3;
		} else 
		//読み込んだキーワードが「vn」なら法線データカウンターをカウントアップ
		if(strcmp(key,"vn")==0) {
			NCnt++;
		} else 
		//読み込んだキーワードが「vt」ならテクスチャーコードデータカウンターをカウントアップ
		if(strcmp(key,"vt")==0) {
			TCnt++;
		} else 
		//読み込んだキーワードが「mtllib」ならマテリアルファイルの読み込み
		if(strcmp(key,"mtllib")==0) {
			char str[32];
			fscanf_s(fp,"%s",str,32);
			LoadMaterial(str);
		}
	}
	printf("VCnt %d\n",VCnt);

	//座標データの数だけ配列を作成
	CVector3D *pVertex = new CVector3D[VCnt];
	//法線データの数だけ配列を作成
	CVector3D *pNormal = new CVector3D[NCnt];
	//テクスチャーコードデータの数だけ配列を作成
	CVector2D *pTexCoord = new CVector2D[TCnt];
	
	for(int i=0;i<m_materialCnt;i++) {
		//描画用頂点配列を作成
		m_mesh[i].m_pVertexAry = new CVector3D[m_mesh[i].m_vertexNum];
		//描画用法線配列を作成
		m_mesh[i].m_pNormalAry = new CVector3D[m_mesh[i].m_vertexNum];
		//描画用テクスチャーコード配列を作成
		m_mesh[i].m_pTexCoordAry = new CVector2D[m_mesh[i].m_vertexNum];

		m_mesh[i].m_vertexNum=0;

	}
	//読み込んだ座標データを0から順番に格納するため、カウンターを0に戻す
	VCnt=0;
	NCnt=0;
	TCnt=0;
	//読み書きの位置をファイルの先頭に戻す
	fseek(fp,0,SEEK_SET);
	//描画用頂点配列への座標データ格納先番号
	int idx = 0;
	//ファイルの末尾でなければ繰り返す
	while(!feof(fp)) {
		//keyをクリア
		key[0]=0;
		//キーワードの読み込み
		fscanf_s(fp,"%s",key,32);
		//「ｖ」を読み込んだら、座標データを読み込む
		if(strcmp(key,"v")==0) {
			fscanf_s(fp,"%f %f %f",&pVertex[VCnt].x,&pVertex[VCnt].y,&pVertex[VCnt].z);
			//読み込み先を次のデータへ
			VCnt++;
		}else//「vn」を読み込んだら、法線データを読み込む
		if(strcmp(key,"vn")==0) {
			fscanf_s(fp,"%f %f %f",&pNormal[NCnt].x,&pNormal[NCnt].y,&pNormal[NCnt].z);
			//読み込み先を次のデータへ
			NCnt++;
		}else//「vt」を読み込んだら、テクスチャーコードデータを読み込む
		if(strcmp(key,"vt")==0) {
			fscanf_s(fp,"%f %f",&pTexCoord[TCnt].x,&pTexCoord[TCnt].y);
			pTexCoord[TCnt].y = 1.0f - pTexCoord[TCnt].y;
			//読み込み先を次のデータへ
			TCnt++;
		} else 
		if(strcmp(key,"usemtl")==0) {
			char name[32];
			fscanf_s(fp,"%s",name,32);
			for(int i=0;i<m_materialCnt;i++) {
				if(strcmp(name,m_mesh[i].m_materialname)==0) {
					m = &m_mesh[i];
				}
			}
		}
		if(strcmp(key,"f")==0) {
			int v1,v2,v3;
			int n1,n2,n3;
			int t1,t2,t3;
			fscanf_s(fp,"%d/%d/%d %d/%d/%d %d/%d/%d",&v1,&t1,&n1,&v2,&t2,&n2,&v3,&t3,&n3);
			m->m_pVertexAry[m->m_vertexNum] = pVertex[v1-1];			//頂点１の座標データ
			m->m_pVertexAry[m->m_vertexNum+1] = pVertex[v2-1];		//頂点２の座標データ
			m->m_pVertexAry[m->m_vertexNum+2] = pVertex[v3-1];		
			
			m->m_pNormalAry[m->m_vertexNum] = pNormal[n1-1];			//頂点１の法線データ
			m->m_pNormalAry[m->m_vertexNum+1] = pNormal[n2-1];		//頂点２の法線データ
			m->m_pNormalAry[m->m_vertexNum+2] = pNormal[n3-1];		
			
			m->m_pTexCoordAry[m->m_vertexNum] = pTexCoord[t1-1];			//頂点１のテクスチャーコードデータ
			m->m_pTexCoordAry[m->m_vertexNum+1] = pTexCoord[t2-1];		//頂点２のテクスチャーコードデータ
			m->m_pTexCoordAry[m->m_vertexNum+2] = pTexCoord[t3-1];		
			
			//データの格納先を3つ移動する
			m->m_vertexNum+=3;
		}
	}
	fclose(fp);


	for (int i = 0; i < m_materialCnt; i++) {
		m_mesh[i].SendBuffer();
	}

	
	m_shader = new CShader("shader\\mesh.vert","shader\\mesh.flag");


	//一時データ解放
	delete[] pVertex;
	delete[] pNormal;
	delete[] pTexCoord;
	return true;
}

void CModelObj::RenderM(CMatrix &m) {
//	UpdateMatrix();
	glPushMatrix();
	glMultMatrixf(m.f);
	m_shader->enable();
	SendShaderParam();


	for(int i=0;i<m_materialCnt;i++) {
		m_mesh[i].Render(m_shader);
	}
	
	m_shader->disable();
	glPopMatrix();


}

void CModelObj::Release() {
	for(int i=0;i<m_materialCnt;i++) {
		m_mesh[i].Release();
	}
}
void CModelObj::setAlpha(float alpha,int no){
	if(no==-1) {
		for(int i=0;i<m_materialCnt;i++) {
			m_mesh[i].m_material.m_alpha = alpha;
		}
	} else {
		m_mesh[no].m_material.m_alpha = alpha;
	}
}