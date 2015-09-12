#pragma once
#include "Include.h"

#include "CM_Img_Block.h"

//マップの自動生成を行う
class CM_Sys_MapGenerator : public GameTask
{
private:
	int									m_Level;		//マップの難易度　１繋ぎのブロック量を決める
	int									m_Group;
	GameTaskPointerList<CM_Img_Block>	m_Img_Block;	//ブロックデータ

	std::vector<CVector2D>				m_AddList;		//追加済み座標リスト

	CFont m_Debug{ L"メイリオ", 50 };

private:
	bool PositionCollision(CVector2D target);

	void CreateBlock(CVector2D start, const int back = -1);
	void CrashBlock(int group);

public:
	CM_Sys_MapGenerator(const int level, const int depth);

protected:
	void Update();
};