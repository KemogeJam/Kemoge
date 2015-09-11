#include "CScene.h"

CScene::~CScene()
{

}

ESceneChange CScene::Update()
{
	return ESceneChange::Main;
}