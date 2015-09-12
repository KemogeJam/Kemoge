#pragma once
#include "Include.h"
#include "GameStatus.h"
#include "StageParameter.h"

//ゲーム中のパラメータを管理するクラスです。
public class CM_ParameterSystem {
private:
	GameStatus m_GameStatus;
	StageParameter m_StageParameter;

	float m_PlayTime = 0.0f; //ゲームプレイ時間
	bool m_IsGameOver = false; //ゲームオーバーしたかどうか
	bool m_IsWallowing = false; //溺れているかどうか

public:
	//初期化処理
	void Init();

	//更新処理
	void Update();

	//ブロックを掘ったときに呼びます
	void BreakBlock(int count);

	//ミミズを入手したときに呼びます
	void ObtainWarm();

	//進んだ時に呼びます
	void GoForward();

	//温泉に溺れているかどうかを設定します
	void SetWallowSpring(bool isWallowing);

	GameStatus GetGameStatus() { return m_GameStatus; }
	StageParameter GetStageParameter() { return m_StageParameter; }

	//UI表示用////////////////////////////////////

	//残りの距離を取得します
	int GetRemainDepth();

	//スコアを取得します
	int GetScore();

	//体力を取得します
	int GetEnergy();

	//残機を取得します
	int GetLife();

};