//Copyright © 2015 Rinifisu
//http://rinifisu.blog.jp/

#pragma once

#include <vector>

#include "Easing.h"
#include "Stopwatch.h"

//滑らかな動作を提供するイージングを管理するクラス
class EasingManager
{
private:
	//// 設定パラメータ ////

	double m_Start;				//開始
	double m_End;				//終了

	double m_TargetMilli;		//目標時間

	//// イージングの種類 ////

	std::function<double(double)> m_Type;

	//// 時間計測 ////

	Stopwatch m_Watch;

public:
	EasingManager();
	EasingManager(double start, double end, std::function<double(double)> easeType = EaseType::Linear, double targetMilli = 1000);

	void SetStart(double start);
	double GetStart();

	void SetEnd(double end);
	double GetEnd();

	void Swap();

	void Reverse();
	void Reverse(bool start, bool end);

	void SetType(std::function<double(double)> easeType);

	void SetTargetTime(double targetMilli);
	double GetTargetTime();

	double GetTime();

	void Start();
	void Stop();
	void Reset();

	bool isActive();
	bool isStop();
	bool isReset();
	bool isEnd();

	double In();
	double Out();
	double InOut();

	double In(double timeMilli);
	double Out(double timeMilli);
	double InOut(double timeMilli);

	double In(int percentage);
	double Out(int percentage);
	double InOut(int percentage);
};

//EasingManager の 自動再生・自動終了・自動初期化・終了値取得 を提供する静的クラス
class EasingSupporter
{
private:
	static EasingSupporter* msp_Instance;

private:
	bool Check(const std::vector<EasingManager*>& easingManager, bool(EasingManager::*func)(), const bool checkBool);
	void Call(const std::vector<EasingManager*>& easingManager, void(EasingManager::*func)());

public:
	/// <summary>
	/// <para>──────────────────────</para>
	/// <para>指定した EasingManager のサポートを行います。</para>
	/// <para>──────────────────────</para>
	/// <para>true  -> Easing が動作中（自動で動作開始します）</para>
	/// <para>false -> Easing が動作終了（自動で初期化します）</para>
	/// <para>──────────────────────</para>
	/// </summary>
	static bool Auto(std::vector<EasingManager*> easingManager, bool autoReset = true, bool autoSwap = false);
};