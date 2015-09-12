#pragma once

//様々な機能
#include "Include.h"

//別クラス間でやり取りが必要な変数
class CGlobal
{
private:
	static std::map<std::string, CImage>		m_Image;	//画像
	static std::map<std::string, TexturePacker>	m_Rect;		//画像範囲

public:
	static float								m_Camera;	//カメラの位置

public:
	static void Load_Image(std::string path);				//画像と画像範囲データの読み込み
	static void Release_Image(std::string path);			//画像と画像範囲データの解放

	static const CImage & Get_Image(std::string path, std::string name);		//画像の取得
	static const TextureRect & Get_Rect(std::string path, std::string name);	//画像範囲の取得
	static const std::vector<TextureRect> & GetArray_Rect(std::string path, std::vector<std::string> name);	//画像範囲の取得
};

//タスク優先順位
enum class EPriority
{
	//MainGame
	CM_Img_Test = 0,
	CM_Sys_GameMap,

	CM_Img_Block,

	CM_Img_Number,
	CM_Img_Player,
	CM_Img_GameMap,

	//その他
};