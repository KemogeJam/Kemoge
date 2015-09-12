#pragma once
#include "Include.h"
#include "AnimationDetail.h"

//�A�j���[�V��������摜�N���X�ł�
public class AnimationImage : public GameTask {
private:

public:
	AnimationImage();

	//�A�j���[�V������ǉ����܂�
	int add(AnimationDetail detail);
	//�A�j���[�V������؂�ւ��܂�
	void change(int animationId);

protected:
	void Update();
	void Draw();

	TexturePacker m_Texture; //�A�j���[�V�����Ɏg���A�g���X
	CImage m_Image; //���ݕ\������Ă���摜
	std::vector<AnimationDetail> m_Details; //�o�^����Ă���A�j���[�V����
	int m_NowPlayAnimationId = 0; //���ݍĐ�����Ă���A�j���[�V����ID
	int m_NowPlayAnimationIndex = 0; //���ݍĐ�����Ă���A�j���[�V�����̃C���f�b�N�X
	float m_RemainComaTime = 0.0f; //���ݕ\������Ă���R�}�̎c�莞��
};
