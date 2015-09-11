//Copyright © 2015 Rinifisu
//http://rinifisu.blog.jp/

#include "Stopwatch.h"

Stopwatch::Stopwatch() : m_Active(false), m_Stop(false), m_Reset(true), m_Memory_Pos(0.0), m_Memory_Stop(0.0)
{
	//システムの１秒間のカウント数（周波数）を取得
	QueryPerformanceFrequency(&m_Freq);
}

void Stopwatch::Start()
{
	m_Active = true;

	if (m_Reset)
	{
		//現在のシステムのカウント数を取得
		QueryPerformanceCounter(&m_Buf);
		m_Memory_Stop = 0.0;

		m_Reset = false;
	}
	else if (m_Stop)
	{
		LARGE_INTEGER tmpTime;
		QueryPerformanceCounter(&tmpTime);

		m_Memory_Stop += static_cast<double>(tmpTime.QuadPart) - static_cast<double>(m_Space.QuadPart);

		m_Stop = false;
	}
}

void Stopwatch::Stop()
{
	if (m_Reset) return;

	m_Active = false;

	if (!m_Stop)
	{
		QueryPerformanceCounter(&m_Space);

		m_Stop = true;
	}
}

void Stopwatch::Reset()
{
	m_Active = false;
	m_Stop = false;
	m_Reset = true;
}

bool Stopwatch::isActive()
{
	return m_Active;
}

bool Stopwatch::isStop()
{
	return m_Stop;
}

bool Stopwatch::isReset()
{
	return m_Reset;
}

double Stopwatch::GetTime_Core()
{
	if (m_Reset)
	{
		return 0.0;
	}
	else if (m_Active)
	{
		LARGE_INTEGER tmpTime;
		QueryPerformanceCounter(&tmpTime);

		m_Memory_Pos = static_cast<double>(tmpTime.QuadPart);
	}

	return (m_Memory_Pos - static_cast<double>(m_Buf.QuadPart) - m_Memory_Stop) / static_cast<double>(m_Freq.QuadPart);
}

double Stopwatch::GetTime_Second()
{
	return GetTime_Core();
}

double Stopwatch::GetTime_Milli()
{
	return GetTime_Core() * 10E+2;
}

/*
double Stopwatch::GetTime_Micro()
{
	return GetTime_Core() * 10E+5;
}

double Stopwatch::GetTime_Nano()
{
	return GetTime_Core() * 10E+8;
}

double Stopwatch::GetTime_Pico()
{
	return GetTime_Core() * 10E+11;
}

double Stopwatch::GetTime_Femto()
{
	return GetTime_Core() * 10E+14;
}
*/