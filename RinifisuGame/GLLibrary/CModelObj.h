/*!
*	@brief	OBJ用モデルクラス
*
*
**/
#pragma once
#include "CTexture.h"
#include "CModel.h"
/*!
		@brief	マテリアルクラス
**/
class CMaterialObj {
public:
	float m_ambient[4];		//アンビエントカラー
	float m_diffuse[4];		//デフューズカラー
	float m_specular[4];	//スペキュラーカラー
	float m_shininess;		//スペキュラー係数
	float m_alpha;
	CVector2D m_st;
	CTexture *m_pTex;		//テクスチャー
public:
	CMaterialObj();
	/*!
		@brief	マテリアルを反映
		@param	shader		[in]	シェーダーオブジェクト
		@retval	無し
	**/
	void Map(CShader *shader);
	
	/*!
		@brief	マテリアル（のテクスチャー）を無効化
		@retval	無し
	**/
	void Unmap();

	/*!
		@brief	マテリアル（のテクスチャー）解放

		@retval	無し
	**/
	void Release();
};

class CMeshObj {
public:
	GLuint		m_buffers[3];
	CVector3D*	m_pVertexAry;		//頂点座標配列
	CVector3D*	m_pNormalAry;		//法線配列
	CVector2D*	m_pTexCoordAry;		//テクスチャーコード配列
	int			m_vertexNum;		//頂点数
	CMaterialObj	m_material;		//マテリアルデータ
	char		m_materialname[32];	//マテリアル名

	CMeshObj();
	void SendBuffer();
	void Render(CShader *shader);
	void Release();
};
/*!
		@brief	OBJファイル用モデルクラス
**/
class CModelObj : public CModel {
private:
	
	CMeshObj *m_mesh;
	int		m_materialCnt;
	/*!
		@brief	マテリアルデータの読み込み
		@param	path		[in]	ファイル名
		@retval	無し
	**/
	bool	LoadMaterial(char *path);
public:

	/*!
		@brief	コンストラクタ
	**/
	CModelObj();

	/*!
		@brief	デストラクタ
	**/
	~CModelObj();

	/*!
		@brief	OBJファイルからモデルデータを読み込む
		@param	path				[in] ファイル名
		@retval	無し
	**/
	bool	Load(const char *path);

	/*!
		@brief	描画を行う
		@param	m				[in] ワールド行列
		@retval	無し
	**/
	void	RenderM(CMatrix &m);

	/*!
		@brief	モデルデータを破棄する
		@retval	無し
	**/
	void	Release();

	CMaterialObj	*getMaterial(int no) {
		return &m_mesh[no].m_material;
	}
	void	setAlpha(float alpha,int no=-1);

};