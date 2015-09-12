#pragma once

//ステージを構成するパラメータです。
struct StageParameter {
	int m_Depth; //ステージの深さ
	float m_ConnectionPercent; //隣を見に行く確率
	float m_DamagePerSecond; // 1秒あたりに受けるダメージ量
};