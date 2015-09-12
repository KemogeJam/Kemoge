#pragma once
#include "Include.h"
#include "AnimationImage.h"

public class CharacterImage : public AnimationImage {
private:
	TextureRect m_AnimationRect;

public:
	enum EAnimationId {
		E_Idle = 0,
		E_Walk = 1,
	};

	CharacterImage();

protected:
	void Update();
	void Draw();
};