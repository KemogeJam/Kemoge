#pragma once
#include "Include.h"

//ゲームの状態を表示するビュークラスです。
class CM_View_State : public GameTask
{
private:
	static const int DEPTH_NUMBER_MAX = 4; //深さの数値の桁数
	static const int PTS_NUMBER_MAX = 7; //スコアの数値の桁数
	CImage m_Image_Background;//背景
	CImage m_Image_Destination; //～まであと
	CImage m_Images_Depth[DEPTH_NUMBER_MAX]; //深さの数値
	CImage m_Images_Pts[PTS_NUMBER_MAX]; //スコアの数値
	CImage m_Image_Life; //残機の数値
	CImage m_Image_GaugeFrame; //メーターの枠
	CImage m_Image_GaugeBackground; //メーターの背景
	CImage m_Image_GaugeGreen; //緑メーター
	CImage m_Image_GaugeYellow; //黄色メーター
	CImage m_Image_GaugeRed; //赤メーター
	CImage m_Image_Face; //顔


public:
	CM_View_State();

	//深さの数値を更新します
	void UpdateDepthCount(int depth);

	//深さのタイプを変更します
	void ChangeDepthType();

	//スコアの数値を更新します
	void UpdatePts(int pts);

	//体力を更新します
	void UpdateEnergy(int energy);

	//残機を更新します
	void UpdateLife(int life);

protected:
	void Update();
	void Draw();
};