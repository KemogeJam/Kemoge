/*!
*	@brief	モデルの基本クラス
*
*
**/
#pragma once

#include "CMatrix.h"
#include "CShader.h"

class CModel {
public:
	CVector3D m_pos;	//座標		
	CVector3D m_rot;	//回転値
	CVector3D m_scale;	//スケール値
	
	CVector3D m_baserot;	//回転値

	CMatrix m_matrix;	//ワールド（モデル）行列
	CMatrix m_transMtx;	//平行移動行列
	CMatrix m_rotMtx;	//回転行列
	CMatrix m_scaleMtx;	//スケーリング行列

	
	CShader		*m_shader;	//シェーダー

public:
	/*!
		@brief	コンストラクタ

	**/
	CModel() : m_pos(0,0,0),m_rot(0,0,0),m_scale(1,1,1),m_baserot(0,0,0) {
	}

	/*!
		@brief	座標を設定する
		@param	pos				[in] 座標
		@retval	無し
	**/
	void setPos(CVector3D pos){
		m_pos = pos;
	}
	/*!
		@brief	座標を設定する
		@param	x				[in] x座標
		@param	y				[in] y座標
		@param	z				[in] z座標
		@retval	無し
	**/
	void setPos(float x,float y,float z){
		m_pos.x = x;
		m_pos.y = y;
		m_pos.z = z;
	}	

	/*!
		@brief	座標を取得する
		@retval 座標
	**/
	CVector3D getPos(){
		return m_pos;
	}
	/*!
		@brief	回転値を設定する
		@param	rot				[in] 回転値
		@retval	無し
	**/

	void setRot(CVector3D rot){
		m_rot = rot;
	}

	/*!
		@brief	基礎回転値を設定する(モデルが前後逆になっている等用)
		@param	x				[in] x軸回転値
		@param	y				[in] y軸回転値
		@param	z				[in] z軸回転値
		@retval	無し
	**/
	void seBasetRot(float x,float y,float z){
		m_baserot.x = x;
		m_baserot.y = y;
		m_baserot.z = z;
	}
	/*!
		@brief	回転値を設定する
		@param	x				[in] x軸回転値
		@param	y				[in] y軸回転値
		@param	z				[in] z軸回転値
		@retval	無し
	**/
	void setRot(float x,float y,float z){
		m_rot.x = x;
		m_rot.y = y;
		m_rot.z = z;
	}

	/*!
		@brief	回転値を取得する
		@retval	回転値
	**/
	CVector3D getRot(){
		return m_rot;
	}

	/*!
		@brief	スケールを設定する
		@param	scale			[in] スケール値
		@retval	無し
	**/

	void setScale(CVector3D scale){
		m_scale = scale;
	}
	
	/*!
		@brief	スケール値を設定する
		@param	x				[in] x軸スケール
		@param	y				[in] y軸スケール
		@param	z				[in] z軸スケール
		@retval	無し
	**/
	void setScale(float x,float y,float z){
		m_scale.x = x;
		m_scale.y = y;
		m_scale.z = z;
	}

	/*!
		@brief	スケール値を取得す
		@retval	スケール値
	**/
	CVector3D getScale(){
		return m_scale;
	}

	/*!
		@brief	平行移動行列を取得する
		@retval	平行移動魚行列
	**/
	CMatrix getTransMatrix() {
		return m_transMtx;
	}

	/*!
		@brief	回転行列を取得する
		@retval	回転行列
	**/
	CMatrix getRotMatrix() {
		return m_rotMtx;
	}
	/*!
		@brief	スケーリング行列を取得する
		@retval	スケーリング行列
	**/
	CMatrix getScaleMatrix() {
		return m_scaleMtx;
	}

	/*!
		@brief	座標、回転値、スケール値からワールド行列を作成する
		@retval	無し
	**/
	void UpdateMatrix();

	/*!
		@brief	ワールド行列を設定する
		@param	m				[in] 行列
		@retval	無し
	**/
	void setMatrix(CMatrix &m){
		m_matrix = m;
	}
	/*!
		@brief　ワールド行列を取得する
		@retval	ワールド行列
	**/
	CMatrix getMatrix(){
		return m_matrix;
	}

	/*!
		@brief	ファイルからモデルを読み込む
		@retval	結果　true成功 false失敗
	**/
	virtual bool Load(const char *path)=0;
	
	/*!
		@brief	行列を指定して描画する
		@param	m				[in] ワールド行列
		@retval	無し
	**/
	virtual void RenderM(CMatrix &m)=0;

	/*!
		@brief	描画する
		@retval	無し
	**/
	virtual void Render(){
		UpdateMatrix();
		RenderM(m_matrix);
	}
	/*!
		@brief	描画する
		@retval	無し
	**/
	virtual void RenderBuilbord(CMatrix m){
		UpdateMatrix();
		RenderM(m_matrix*m);
	}


	/*!
		@brief	モデルを破棄する
		@retval	無し
	**/
	virtual void Release()=0;

	
	virtual void SendShaderParam();


};