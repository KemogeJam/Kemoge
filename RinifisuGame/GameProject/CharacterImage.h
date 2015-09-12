#pragma once
#include "Include.h"
#include "AnimationImage.h"

public class CharacterImage : public AnimationImage {
private:
	TextureRect m_AnimationRect;

public:
	enum EAnimationId {
		E_IdleLeft = 0,
		E_IdleRight = 1,
		E_DigLeft = 2,
		E_DigRight = 3,
		E_DigDown = 4,
		E_DigUp = 5,
		E_WalkLeft = 6,
		E_WalkRight = 7
	};

	CharacterImage();

protected:
	void Update();
	void Draw();
};