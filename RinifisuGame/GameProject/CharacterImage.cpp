#include "CharacterImage.h"

CharacterImage::CharacterImage() {
	m_AnimationRect = TextureRect{ 400, 400, 80, 80 };
	//通常アニメーション
	AnimationDetail idle = AnimationDetail{};
	for (int i = 0; i < 8; i++) {
		CVector2D pos = CVector2D(40 * i + 320, 320);
		idle.m_Positions.push_back(pos);
	}
	idle.m_Size = CVector2D{ 100.0f, 100.0f };
	idle.m_IsLoop = true;
	idle.m_ComaPerFrame = 0.1f;
	add(idle);

	m_NowPlayAnimationId = EAnimationId::E_Idle;
}

void CharacterImage::Update() {
	AnimationImage::Update();
}

void CharacterImage::Draw() {
	AnimationImage::Draw();
}