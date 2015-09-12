#include "AnimationImage.h"

AnimationImage::AnimationImage()
	: GameTask({ BIND(AnimationImage::Update) }, 0, 0)
{

}

//�A�j���[�V������o�^���܂�
int AnimationImage::add(AnimationDetail detail) {
	m_Details.push_back(detail);
	return m_Details.size() - 1;
}

//�A�j���[�V������؂�ւ��܂�
void AnimationImage::change(int animationId) {
	AnimationDetail detail = m_Details.at(m_NowPlayAnimationId);
	m_NowPlayAnimationId = animationId;
	m_NowPlayAnimationIndex = 0;
	m_RemainComaTime = detail.m_ComaPerFrame;
}


void AnimationImage::Update() {
	AnimationDetail detail = m_Details.at(m_NowPlayAnimationId);
	CVector2D position = detail.m_Positions.at(m_NowPlayAnimationIndex);
	m_Image.setRect(position.x, position.y, position.x + detail.m_Size.x, position.y + detail.m_Size.y);
	m_Image.setSize(detail.m_Size.x, detail.m_Size.y);

	m_RemainComaTime -= 0.0166f;
	//�R�}�̕\�����Ԃ������Ȃ�����A���̃R�}�ɕς��
	if (m_RemainComaTime < 0.0f) {
		m_RemainComaTime += detail.m_ComaPerFrame;
		if (m_NowPlayAnimationIndex < detail.m_Positions.size() - 1) {
			m_NowPlayAnimationIndex++;
		}
		else {
			m_NowPlayAnimationIndex = 0;
		}
	}
}

void AnimationImage::Draw() {
	m_Image.Draw();
}