
/*!
*		@brief	シェーダー用光源クラス
*
**/
#pragma once
#include "GL.h"
#include "CVector.h"


class CLight {
public:
	enum {
		eLight_None=0,		//光源無効
		eLight_Direction,	//環境光
		eLight_Point,		//全方向ポイント光
		eLight_Spot,		//スポットライト
	};
	static const int LIGHT_MAX = 5;
	static CVector3D	m_lightPos[LIGHT_MAX];
	static CVector3D	m_lightDir[LIGHT_MAX];
	static CVector3D	m_AmbientColor[LIGHT_MAX];
	static CVector3D	m_DiffuseColor[LIGHT_MAX];
	static int			m_Type[LIGHT_MAX];
	static float		m_Attenuation[LIGHT_MAX];
	static float		m_RadiationAngle[LIGHT_MAX];
	static int			m_Lighting;
	
private:
public:
	
	/*!
		@brief	光源の有無を設定する
		@retval	無し
	**/
	static void setLighting(bool f){
		if(f) m_Lighting = 1;
		else m_Lighting=0;
	}
	/*!
		@brief	光源の有無を取得する
		@retval	
	**/
	static int getLighting(){
		return m_Lighting;
	}
	/*!
		@brief	光源の位置を設定する
		@param	no		[in] 光源番号
		@param	v		[in] 位置
		@retval	無し
	**/
	static void setPos(int no,CVector3D v){
		m_lightPos[no] = v;
	}

	/*!
		@brief	光源の向きを設定する
		@param	no		[in] 光源番号
		@param	v		[in] 向きベクトル
		@retval	無し
	**/
	static void setDir(int no,CVector3D v){
		m_lightDir[no] = v;
	}

	
	/*!
		@brief	光源の種類を設定する
		@param	no		[in] 光源番号
		@param	type	[in] 光源の種類
		@retval	無し
	**/
	static void setType(int no,int type){
		m_Type[no] = type;
	}

	
	/*!
		@brief	光源の減衰率を設定する
		@param	no				[in] 光源番号
		@param	Attenuation		[in] 減衰率
		@retval	無し
	**/
	static void setAttenuation(int no,float Attenuation){
		m_Attenuation[no] = Attenuation;
	}

	/*!
		@brief	光源の広角を設定する
		@param	no				[in] 光源番号
		@param	RadiationAngle	[in] 角度
		@retval	無し
	**/
	static void setRadiationAngle(int no,float RadiationAngle){
		m_RadiationAngle[no] = RadiationAngle;
	}

	/*!
		@brief	光源の色を設定する
		@param	no				[in] 光源番号
		@param	a				[in] アンビエント（環境光）
		@param	d				[in] デフューズ（拡散反射光）
		@retval	無し
	**/
	static void setColor(int no,CVector3D a,CVector3D d){
		m_AmbientColor[no]  = a;
		m_DiffuseColor[no]  = d;
	}


	/*!
		@brief	光源の位置を取得する
		@param	no				[in] 光源番号
		@retval	位置
	**/
	static CVector3D getPos(int no){
		return m_lightPos[no];
	}
	
	/*!
		@brief	光源のアンビエントカラーを取得する
		@param	no				[in] 光源番号
		@retval	アンビエント（環境光）
	**/
	static CVector3D getAmbientColor(int no){
		return m_AmbientColor[no];
	}
	
	/*!
		@brief	光源のデフューズカラーを取得する
		@param	no				[in] 光源番号
		@retval	デフューズ（拡散反射光）
	**/
	static CVector3D getDiffuseColor(int no){
		return m_DiffuseColor[no];
	}


	
	/*!
		@brief	光源の位置配列のアドレスを取得する（シェーダー用）
		@retval	位置配列のアドレス
	**/
	static CVector3D *getPosPointer(){
		return m_lightPos;
	}

	/*!
		@brief	光源の向き配列のアドレスを取得する（シェーダー用）
		@retval	向き配列のアドレス
	**/
	static CVector3D *getDirPointer(){
		return m_lightDir;
	}

	
	/*!
		@brief	光源のアンビエントカラー配列のアドレスを取得する（シェーダー用）
		@retval	アンビエントカラー配列のアドレス
	**/
	static CVector3D *getAmbientColorPointer(){
		return m_AmbientColor;
	}
	
	/*!
		@brief	光源のデフューズカラー配列のアドレスを取得する（シェーダー用）
		@retval	デフューズカラー配列のアドレス
	**/
	static CVector3D *getDiffuseColorPointer(){
		return m_DiffuseColor;
	}
	
	/*!
		@brief	光源の種類配列のアドレスを取得する（シェーダー用）
		@retval	種類配列のアドレス
	**/
	static int *getTypeColorPointer(){
		return m_Type;
	}
	
	/*!
		@brief	光源の減衰率配列のアドレスを取得する（シェーダー用）
		@retval	減衰率配列のアドレス
	**/
	static float *getAttenuationPointer(){
		return m_Attenuation;
	}

	
	/*!
		@brief	光源の広角配列のアドレスを取得する（シェーダー用）
		@retval	広角配列のアドレス
	**/
	static float *getRadiationAnglePointer(){
		return m_RadiationAngle;
	}

};