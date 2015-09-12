#pragma once

//ゲームプレイにおけるステータスです。
struct GameStatus {
	int m_DownDepth; //下りの進んだ距離
	int m_UpDepth; //上りの進んだ距離
	int m_Score; //スコア
	float m_Energy; //体力
	int m_Life; //残機
};