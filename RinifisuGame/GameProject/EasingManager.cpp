//Copyright © 2015 Rinifisu
//http://rinifisu.blog.jp/

#include "EasingManager.h"

EasingManager::EasingManager()
{

}

EasingManager::EasingManager(double start, double end, std::function<double(double)> easeType, double targetMilli)
	: m_Start(start), m_End(end), m_Type(easeType), m_TargetMilli(targetMilli), m_Watch()
{

}

void EasingManager::SetStart(double start)
{
	m_Start = start;
}

double EasingManager::GetStart()
{
	return m_Start;
}

void EasingManager::SetEnd(double end)
{
	m_End = end;
}

double EasingManager::GetEnd()
{
	return m_End;
}

void EasingManager::Swap()
{
	std::swap(m_Start, m_End);
}

void EasingManager::Reverse()
{
	m_Start = !m_Start;
	m_End = !m_End;
}

void EasingManager::Reverse(bool start, bool end)
{
	if (start) m_Start = !m_Start;
	if (end) m_End = !m_End;
}

void EasingManager::SetType(std::function<double(double)> easeType)
{
	m_Type = easeType;
}

void EasingManager::SetTargetTime(double targetMilli)
{
	m_TargetMilli = targetMilli;
}

double EasingManager::GetTargetTime()
{
	return m_TargetMilli;
}

double EasingManager::GetTime()
{
	return m_Watch.GetTime_Milli();
}

void EasingManager::Start()
{
	m_Watch.Start();
}

void EasingManager::Stop()
{
	m_Watch.Stop();
}

void EasingManager::Reset()
{
	m_Watch.Reset();
}

bool EasingManager::isActive()
{
	if (m_Watch.isActive())
	{
		if (m_TargetMilli < m_Watch.GetTime_Milli())
		{
			return false;
		}

		return true;
	}

	return false;
}

bool EasingManager::isStop()
{
	return m_Watch.isStop();
}

bool EasingManager::isReset()
{
	return m_Watch.isReset();
}

bool EasingManager::isEnd()
{
	return m_TargetMilli < m_Watch.GetTime_Milli();
}

double EasingManager::In()
{
	return EaseMode::In(m_Start, m_End, m_Type, m_Watch.GetTime_Milli() / m_TargetMilli);
}

double EasingManager::Out()
{
	return EaseMode::Out(m_Start, m_End, m_Type, m_Watch.GetTime_Milli() / m_TargetMilli);
}

double EasingManager::InOut()
{
	return EaseMode::InOut(m_Start, m_End, m_Type, m_Watch.GetTime_Milli() / m_TargetMilli);
}

double EasingManager::In(double timeMilli)
{
	return EaseMode::In(m_Start, m_End, m_Type, timeMilli / m_TargetMilli);
}

double EasingManager::Out(double timeMilli)
{
	return EaseMode::Out(m_Start, m_End, m_Type, timeMilli / m_TargetMilli);
}

double EasingManager::InOut(double timeMilli)
{
	return EaseMode::InOut(m_Start, m_End, m_Type, timeMilli / m_TargetMilli);
}

double EasingManager::In(int percentage)
{
	return EaseMode::In(m_Start, m_End, m_Type, static_cast<double>(percentage) / 100.0);
}

double EasingManager::Out(int percentage)
{
	return EaseMode::Out(m_Start, m_End, m_Type, static_cast<double>(percentage) / 100.0);
}

double EasingManager::InOut(int percentage)
{
	return EaseMode::InOut(m_Start, m_End, m_Type, static_cast<double>(percentage) / 100.0);
}

EasingSupporter* EasingSupporter::msp_Instance = nullptr;

bool EasingSupporter::Check(const std::vector<EasingManager*>& easingManager, bool(EasingManager::*func)(), const bool checkBool)
{
	for (unsigned int i = 0; i < easingManager.size(); i++)
	{
		std::function<bool()> tmpFunc = std::bind(std::mem_fn(func), easingManager[i]);

		if (checkBool == tmpFunc()) return checkBool;
	}

	return !checkBool;
}

void EasingSupporter::Call(const std::vector<EasingManager*>& easingManager, void(EasingManager::*func)())
{
	for (unsigned int i = 0; i < easingManager.size(); i++)
	{
		std::function<void()> tmpFunc = std::bind(std::mem_fn(func), easingManager[i]);
		tmpFunc();
	}
}

bool EasingSupporter::Auto(std::vector<EasingManager*> easingManager, bool autoReset, bool autoSwap)
{
	if (msp_Instance == nullptr) msp_Instance = new EasingSupporter();

	//再生中で、終了したかを確認
	if (msp_Instance->Check(easingManager, &EasingManager::isEnd, false))
	{
		//終了後、すぐにリセットを行ってしまうと、終了値を取得することが不可能になってしまう
		//その対策として、Stop をトグル代わりに利用して、終了値を１度だけ取得可能にする

		//全てが停止状態であるかを確認
		if (msp_Instance->Check(easingManager, &EasingManager::isStop, false))
		{
			//初期化を行う
			if (autoReset) msp_Instance->Call(easingManager, &EasingManager::Reset);

			//最初と最後を逆にする
			if (autoSwap) msp_Instance->Call(easingManager, &EasingManager::Swap);

			//終了
			return false;
		}
		else
		{
			//全てを停止する
			msp_Instance->Call(easingManager, &EasingManager::Stop);
		}
	}
	//再生を行っていないかを確認
	else if (!msp_Instance->Check(easingManager, &EasingManager::isActive, true))
	{
		//再生を開始する
		msp_Instance->Call(easingManager, &EasingManager::Start);
	}

	return true;
}

/*
bool EasingSupporter::ActiveCheck(const std::vector<EasingManager*>& easingManager)
{
	std::vector<EasingManager*>::const_iterator easingIt = easingManager.begin();

	while (easingIt != easingManager.end())
	{
		if ((*easingIt)->isActive()) return true;
		easingIt++;
	}

	return false;
}

bool EasingSupporter::StopCheck(const std::vector<EasingManager*>& easingManager)
{
	std::vector<EasingManager*>::const_iterator easingIt = easingManager.begin();

	while (easingIt != easingManager.end())
	{
		if (!(*easingIt)->isStop()) return false;
		easingIt++;
	}

	return true;
}

bool EasingSupporter::EndCheck(const std::vector<EasingManager*>& easingManager)
{
	std::vector<EasingManager*>::const_iterator easingIt = easingManager.begin();

	while (easingIt != easingManager.end())
	{
		if (!(*easingIt)->isEnd()) return false;
		easingIt++;
	}

	return true;
}

void EasingSupporter::WatchStart(std::vector<EasingManager*>& easingManager)
{
	std::vector<EasingManager*>::iterator easingIt = easingManager.begin();

	while (easingIt != easingManager.end())
	{
		(*easingIt)->Start();
		easingIt++;
	}
}

void EasingSupporter::WatchStop(std::vector<EasingManager*>& easingManager)
{
	std::vector<EasingManager*>::iterator easingIt = easingManager.begin();

	while (easingIt != easingManager.end())
	{
		(*easingIt)->Stop();
		easingIt++;
	}
}

void EasingSupporter::WatchReset(std::vector<EasingManager*>& easingManager)
{
	std::vector<EasingManager*>::iterator easingIt = easingManager.begin();

	while (easingIt != easingManager.end())
	{
		(*easingIt)->Reset();
		easingIt++;
	}
}

bool EasingSupporter::Auto(std::vector<EasingManager*> easingManager, bool autoReset, bool autoSwap)
{
	if (msp_Instance == nullptr) msp_Instance = new EasingSupporter();

	//再生中で、終了したかを確認
	if (msp_Instance->EndCheck(easingManager))
	{
		//終了後、すぐにリセットを行ってしまうと、終了値を取得することが不可能になってしまう
		//その対策として、Stop をトグル代わりに利用して、終了値を１度だけ取得可能にする

		//全てが停止状態であるかを確認
		if (msp_Instance->StopCheck(easingManager))
		{
			//初期化を行う
			if (autoReset) msp_Instance->WatchReset(easingManager);

			//最初と最後を逆にする
			if (autoSwap);

			//終了
			return false;
		}
		else
		{
			//全てを停止する
			msp_Instance->WatchStop(easingManager);
		}
	}
	//再生を行っていないかを確認
	else if (!msp_Instance->ActiveCheck(easingManager))
	{
		//再生を開始する
		msp_Instance->WatchStart(easingManager);
	}

	return true;
}
*/