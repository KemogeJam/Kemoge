#include "CImage.h"
#include "CCamera.h"




CImage::CImage() : m_vPos(0,0),m_vCenter(0,0),m_vSize(0,0),srcRect(0,0,0,0),m_ang(0),m_flipH(false),m_color(1.0f,1.0f,1.0f,1.0f){
}
CImage::~CImage(){
}
bool CImage::Load(char* path){
	bool f=false;
	m_pTexture = new CTexture();
	f = m_pTexture->Load(path);
	if (f){
		setPos(0, 0);
		setRect(0, 0, m_pTexture->m_width, m_pTexture->m_height);
		setSize(static_cast<float>(m_pTexture->m_width), static_cast<float>(m_pTexture->m_height));
	}
	return f;
	

}
void CImage::Release() {
	delete m_pTexture;
}




void CImage::Draw() {
	//各種機能を無効に
	//カリング無効
	glDisable(GL_CULL_FACE);
	//ライティング無効
	glDisable(GL_LIGHTING);
	//デプステスト無効
	glDisable(GL_DEPTH_TEST);
	//
	//正射投影の行列を作成
	//
	CMatrix	mProj = CMatrix(
		2.0f/CCamera::getCurrent()->getWhidth() , 0.0f, 0.0f, -1.0f,
         0.0f, -2.0f/CCamera::getCurrent()->getHeight() , 0.0f, 1.0f,
         0.0f, 0.0f, 1.0f, 0.0f,
         0.0f, 0.0f, 0.0f, 1.0f
     );

	//投影行列を専用の物に設定
    glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadMatrixf(mProj.f);

	//モデル＆ビュー行列を再設定
    glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	CMatrix mT,mR;
	mT.Transelate(m_vPos.x,m_vPos.y,0.0f);
	
	mR.RotationZ(m_ang);

	glLoadMatrixf((mT * mR).f);

	
	m_pTexture->MapTexture();

	//画像を張り付けるためのポリゴンの作成
	struct SVertex {
		float tu;
		float tv;
		float vx;
		float vy;
		float vz;
	};
	SVertex vertices[] = {
		//テクスチャー座標 uv														頂点座標xyz
		{ srcRect.m_left/m_pTexture->m_width,srcRect.m_top/m_pTexture->m_height,0-m_vCenter.x,			0-m_vCenter.y,			0.0f },		//左上
		{ srcRect.m_right/m_pTexture->m_width,srcRect.m_top/m_pTexture->m_height,m_vSize.x-m_vCenter.x,	0-m_vCenter.y,			0.0f },		//右上
		{ srcRect.m_left/m_pTexture->m_width,srcRect.m_bottom/m_pTexture->m_height,0-m_vCenter.x,		m_vSize.y-m_vCenter.y,	0.0f },		//左下
		{ srcRect.m_right/m_pTexture->m_width,srcRect.m_bottom/m_pTexture->m_height,m_vSize.x-m_vCenter.x,m_vSize.y-m_vCenter.y,	0.0f }		//右下
	};
	//左右反転処理
	if(m_flipH) {
		float t = vertices[0].tu;
		vertices[0].tu = vertices[2].tu = vertices[1].tu;
		vertices[1].tu = vertices[3].tu = t;
		
	}


	//カラー設定
	glColor4fv(m_color.v);
	//描画
	glInterleavedArrays(GL_T2F_V3F, 0, vertices);
	glDrawArrays(GL_TRIANGLE_STRIP,0,4);

	m_pTexture->UnmapTexture();

	//元の行列と設定に戻す
	glPopMatrix();
    glMatrixMode(GL_PROJECTION);
	glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	
}