#pragma once

//様々な機能
#include "Include.h"

//その他
#include "CR_Background.h"

enum class EResultScene
{
	Create, //生成
	Wait,	//待機
};

class CResult : public CScene
{
private:
	EResultScene m_Scene;		//シーンの管理

private:
	GameTaskPointer<CR_Background> m_Background;

public:
	CResult();
	~CResult();

	ESceneChange Update();	//シーンを参照して各クラスに命令を与える
};