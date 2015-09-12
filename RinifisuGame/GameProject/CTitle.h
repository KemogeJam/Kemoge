#pragma once

//様々な機能
#include "Include.h"

//その他
#include "CTI_Background.h"

enum class ETitleScene
{
	Create, //生成
	Wait,	//待機
};

class CTitle : public CScene
{
private:
	ETitleScene m_Scene;		//シーンの管理

private:
	GameTaskPointer<CTI_Background> m_Background;

public:
	CTitle();
	~CTitle();

	ESceneChange Update();	//シーンを参照して各クラスに命令を与える
};
