//Copyright © 2015 Rinifisu
//http://rinifisu.blog.jp/

#pragma once
#include <windows.h>

class Stopwatch		//時間を計測するクラス
{
private:
	bool m_Active;	//動作中であるか
	bool m_Stop;	//一時停止中であるか
	bool m_Reset;	//初期化状態であるか

	LARGE_INTEGER m_Buf;	//開始時のカウント	
	LARGE_INTEGER m_Space;	//一時停止中の時間補正
	LARGE_INTEGER m_Freq;	//カウント周波数

	double m_Memory_Pos;	//結果時間を収納
	double m_Memory_Stop;	//結果時間を収納

private:
	double GetTime_Core();	//時間を返す

public:
	Stopwatch();

	/// <summary>
	/// <para>────────────</para>
	/// <para>ストップウォッチを開始します。</para>
	/// <para>────────────</para>
	/// </summary>
	void Start();

	/// <summary>
	/// <para>─────────────</para>
	/// <para>ストップウォッチを一時停止します。</para>
	/// <para>─────────────</para>
	/// </summary>
	void Stop();

	/// <summary>
	/// <para>────────────</para>
	/// <para>ストップウォッチを初期化します。</para>
	/// <para>────────────</para>
	/// </summary>
	void Reset();

	/// <summary>
	/// <para>────────────</para>
	/// <para>動作中であるかを取得します。</para>
	/// <para>────────────</para>
	/// </summary>
	bool isActive();

	/// <summary>
	/// <para>──────────────</para>
	/// <para>一時停止中であるかを取得します。</para>
	/// <para>──────────────</para>
	/// </summary>
	bool isStop();

	/// <summary>
	/// <para>──────────────</para>
	/// <para>初期化状態であるかを取得します。</para>
	/// <para>──────────────</para>
	/// </summary>
	bool isReset();

	/// <summary>
	/// <para>──────────</para>
	/// <para>現在の秒を取得します。</para>
	/// <para>──────────</para>
	/// </summary>
	double GetTime_Second();

	/// <summary>
	/// <para>───────────</para>
	/// <para>現在のミリ秒を取得します。</para>
	/// <para>───────────</para>
	/// </summary>
	double GetTime_Milli();

//	double GetTime_Micro();
//	double GetTime_Nano();
//	double GetTime_Pico();
//	double GetTime_Femto();
};