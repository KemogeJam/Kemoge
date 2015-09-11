/*!
*	@brief	Xファイル（スキンメッシュモデル）用モデルクラス
*
*
**/
#pragma once

#include "GL.h"

#include "CXModelLoader.h"
#include "CTexture.h"
#include "CShader.h"


#include "Vertex.h"
#include "CModel.h"
/*
  モデルの階層構造用クラス
  CXFrameをスキンメッシュ用に派生
*/
class CFrameBone : public CXFrame{
private:
	CMatrix boneMatrix;
	CMatrix sMatrix;
	CMatrix matrixOffset;

	CMatrix blendMatrix;
public:
	CFrameBone():CXFrame(){
	}
	CFrameBone(CXFrame &f){
		setNo(f.getNo());
		setMatrix(f.getMatrix());
		setType(f.getType());
		copyToken(f.getToken());
		copyName(f.getName());
	}
	CMatrix getSMatrix(){
		return sMatrix;

	}
	void saveBlendMatrix() {
		blendMatrix = matrix;
	}
	void calcBlendMatrix(float r) {
		matrix = matrix*r + blendMatrix*(1-r);
	}
	void calcBoneMatrix(CMatrix *out);
	void calcMatrix();
	CMatrix getMatrixOffset(){
		return matrixOffset ;
	}
	void seMatrixOffset(CMatrix mat){
		matrixOffset = mat;
	}
};
/*
  アニメーション管理クラス
  読み込んだアニメーション構造をそのまま使用
*/
class CAnimation {
public:
	struct SAnimData {
		int	start;
		int end;
	};
private:
	std::vector<CXAnimationSet*> *pAnimation;
	float time;
	int jam;
	float speed;
	bool loop;
	int endTime;
	CFrameBone *pBoneRoot;
	float blend;
	float blendS;
	SAnimData *pAnimData;
private:
	CMatrix calcMatrix(CXAnimationKey &key,float t);
public:
	CAnimation();
	CAnimation(std::vector<CXAnimationSet*> &a);
	~CAnimation();
	void Release();
	int getEndTime(int j);
	void changeAnimation(int j,bool l = true,bool check=true,int blendFrame=5);
	void upDate();
	void updateMatrix();
	void saveBlendMatrix();
	bool isEnd(){
		if(time >= endTime-1.0f) return true;
		return false;
	}
	int getJam() {
		return jam;
	}
	void setSpeed(float s) {
		speed = s;
	}
	void attachFrame(CFrameBone *bone){
		pBoneRoot = bone;
	}
	void attachAnimData(SAnimData* p) {
		pAnimData = p;
	}
	
	friend class CModelX;
};
/*
  マテリアルクラス
*/
class CMaterial {
public:
	SXColorRGBA	faceColor;
	float power;
	SXColorRGB	specularColor;
	SXColorRGB	emissiveColor;
	CVector2D	st;
	float alpha;
	CTexture	*texture;
public:
	CMaterial(CXMaterial &m);
	~CMaterial();
	void set(CShader *shader);
	void reset();
};
struct SSkinWeight {
	SXVector4 bone;
	SXVector4 weight;
};


/*
  各頂点に設定されたウェイト値を頂点毎にまとめるクラス
*/
class CSkinWeights {
public:
	SSkinWeight *weight;
public:
	CSkinWeights( CXModelLoader &loader, CXMesh &mesh);
	~CSkinWeights();
};
/*
  ポリゴンクラス
  マテリアル毎にまとめる
*/
class CPoly{
public:
	MY_VERTEX  *m_pVertex;
	int			vertexCnt;
	int			faceCnt;
	bool		bNormal;
	bool		bTexCode;
	bool		bWeight;
	int			material;
	GLuint		buffer;
public:
	/*
	  ローダーからポリゴンデータを構築
	*/
	CPoly( CXModelLoader &loader,  CXMesh &mesh,CSkinWeights *bone,int matNo);
	~CPoly();
	/*
	  描画
	*/
	void draw(CShader *shader);
};
/*
  メッシュ毎のボーンオフセット行列を格納
*/
class CBoneOffset{
public:
	char transformNodeName[64];
	CMatrix matrixOffset;
	CBoneOffset(){
	}
	/*
	  SkinWeightsからボーン名とマトリックスのみを格納
	*/
	CBoneOffset(CXSkinWeights &s){
		strcpy_s(transformNodeName,sizeof(transformNodeName),s.transformNodeName);
		matrixOffset = s.matrixOffset;
	}

};
/*
  メッシュクラス
*/
class CMesh{
private:
	std::vector<CPoly*> polyList;
	std::vector<CBoneOffset*> boneList;
	CMatrix matrix;
public:
	/*
	  ローダーからメッシュデータを構築
	*/
	CMesh(CXModelLoader &loader,  CXMesh &mesh,CSkinWeights *bone);
	~CMesh();
	/*
	  描画
	*/
	void draw(std::vector<CMaterial*> materialList,CShader *shader,CFrameBone *pFrameRoot,CMatrix *boneMatrix,int boneNum);

};

/*
  ｘファイル用モデルクラス
*/
class CModelX : public CModel{
private:
	std::vector<CMesh*> *pMeshList;
	std::vector<CMaterial*> *pMaterialList;
	CFrameBone *pFrameRoot;
	int			boneNum;
	CMatrix *boneMatrix;
	CAnimation *animation;
	void createFrame(CXFrame *xf,CFrameBone *f,int *num);
public:
	CModelX();
	~CModelX();
	void operator = (const CModelX &m);
	void Release();
	/*
	  ローダーからモデルを構築
	*/
	bool Load(CXModelLoader &loader);
	/*
	  ファイルからモデルを構築
	*/
	bool Load(const char* filePath);
	/*
	  アニメーションを更新
	*/
	void UpdateAnimation();
	/*
	  アニメーションの終了を判定
	*/
	bool isAnimationEnd(){
		if(!animation) return true;
		return animation->isEnd();
	}
	/*
	  アニメーションの種類を取得
	*/
	int getAnimationJam(){
		if(!animation) return true;
		return animation->getJam();
	}
	/*
	　アニメーション速度の変更
	*/
	void setAnimationSpeed(float s) {
		animation->setSpeed(s);
	}
	/*
	  アニメーションを切り替える
	*/
	void ChangeAnimation(int jam,bool loop = true,bool check=true,int blendFrame=5){
		if(!animation) return;
		animation->changeAnimation(jam,loop,check,blendFrame);
	}

	void attachAnimData(CAnimation::SAnimData *p) {
		animation->attachAnimData(p);
	}
	/*
	  描画
	*/
	void RenderM(CMatrix &m);

	/*
	　ボーンの行列を取得
	*/
	CMatrix getFrameMatrix(const char *name,bool local=false);
	/*
	　ボーンの行列を取得
	*/
	CMatrix getFrameMatrix(int no,bool local=false);

	void setAlpha(int no,float alpha) {
		(*pMaterialList)[no]->alpha = alpha;
	}
	
	CMaterial *getMaterial(int no){
		return (*pMaterialList)[no];
	}
	friend class CModelX;
};