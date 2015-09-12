#pragma once
#include "Include.h"
#include "AnimationDetail.h"

//アニメーションする画像クラスです
public class AnimationImage : public GameTask {
private:

public:
	AnimationImage();

	//アニメーションを追加します
	int add(AnimationDetail detail);
	//アニメーションを切り替えます
	void change(int animationId);

protected:
	void Update();
	void Draw();

	TexturePacker m_Texture; //アニメーションに使うアトラス
	CImage m_Image; //現在表示されている画像
	std::vector<AnimationDetail> m_Details; //登録されているアニメーション
	int m_NowPlayAnimationId = 0; //現在再生されているアニメーションID
	int m_NowPlayAnimationIndex = 0; //現在再生されているアニメーションのインデックス
	float m_RemainComaTime = 0.0f; //現在表示されているコマの残り時間
};
