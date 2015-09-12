#pragma once

enum class ESceneChange
{
	None,
	Title,
	Tutorial,
	Main,
	Result
};

class CScene
{
public:
	//仮想関数にすることで、小クラスのデストラクタが呼ばれる
	virtual ~CScene();

	virtual ESceneChange Update();
};