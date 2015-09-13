#pragma once
#include "Include.h"

//�Q�[���̏�Ԃ�\������r���[�N���X�ł��B
class CM_View_State : public GameTask
{
private:
	static const int DEPTH_NUMBER_MAX = 4; //�[���̐��l�̌���
	static const int PTS_NUMBER_MAX = 7; //�X�R�A�̐��l�̌���
	CImage m_Image_Background;//�w�i
	CImage m_Image_Destination; //�`�܂ł���
	CImage m_Images_Depth[DEPTH_NUMBER_MAX]; //�[���̐��l
	CImage m_Images_Pts[PTS_NUMBER_MAX]; //�X�R�A�̐��l
	CImage m_Image_Life; //�c�@�̐��l
	CImage m_Image_GaugeFrame; //���[�^�[�̘g
	CImage m_Image_GaugeBackground; //���[�^�[�̔w�i
	CImage m_Image_GaugeGreen; //�΃��[�^�[
	CImage m_Image_GaugeYellow; //���F���[�^�[
	CImage m_Image_GaugeRed; //�ԃ��[�^�[
	CImage m_Image_Face; //��


public:
	CM_View_State();

	//�[���̐��l���X�V���܂�
	void UpdateDepthCount(int depth);

	//�[���̃^�C�v��ύX���܂�
	void ChangeDepthType();

	//�X�R�A�̐��l���X�V���܂�
	void UpdatePts(int pts);

	//�̗͂��X�V���܂�
	void UpdateEnergy(int energy);

	//�c�@���X�V���܂�
	void UpdateLife(int life);

protected:
	void Update();
	void Draw();
};