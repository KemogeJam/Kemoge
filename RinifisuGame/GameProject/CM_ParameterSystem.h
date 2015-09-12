#pragma once
#include "Include.h"
#include "GameStatus.h"
#include "StageParameter.h"

//�Q�[�����̃p�����[�^���Ǘ�����N���X�ł��B
public class CM_ParameterSystem {
private:
	GameStatus m_GameStatus;
	StageParameter m_StageParameter;

	float m_PlayTime = 0.0f; //�Q�[���v���C����
	bool m_IsGameOver = false; //�Q�[���I�[�o�[�������ǂ���
	bool m_IsWallowing = false; //�M��Ă��邩�ǂ���

public:
	//����������
	void Init();

	//�X�V����
	void Update();

	//�u���b�N���@�����Ƃ��ɌĂт܂�
	void BreakBlock(int count);

	//�~�~�Y����肵���Ƃ��ɌĂт܂�
	void ObtainWarm();

	//�i�񂾎��ɌĂт܂�
	void GoForward();

	//����ɓM��Ă��邩�ǂ�����ݒ肵�܂�
	void SetWallowSpring(bool isWallowing);

	GameStatus GetGameStatus() { return m_GameStatus; }
	StageParameter GetStageParameter() { return m_StageParameter; }

	//UI�\���p////////////////////////////////////

	//�c��̋������擾���܂�
	int GetRemainDepth();

	//�X�R�A���擾���܂�
	int GetScore();

	//�̗͂��擾���܂�
	int GetEnergy();

	//�c�@���擾���܂�
	int GetLife();

};