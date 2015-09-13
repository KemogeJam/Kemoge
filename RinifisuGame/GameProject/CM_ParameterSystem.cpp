#pragma once
#include "CM_ParameterSystem.h"


void CM_ParameterSystem::Init() {
	//�v���C�f�[�^������
	m_GameStatus.m_DownDepth = 0;
	m_GameStatus.m_UpDepth = 0;
	m_GameStatus.m_Energy = 100.0f;
	m_GameStatus.m_Life = 3;
	m_GameStatus.m_Score = 0;

	//�X�e�[�W��񏉊���
	m_StageParameter.m_Depth = 100;
	m_StageParameter.m_ConnectionPercent = 20.0f;
	m_StageParameter.m_DamagePerSecond = 1.0f;
}

void CM_ParameterSystem::Update() {
	if (m_IsGameOver) return;

	float deltatime = 0.016f;
	//�v���C�^�C�����Z
	m_PlayTime += deltatime;
	//�G�l���M�[����
	float damage = deltatime * m_StageParameter.m_DamagePerSecond;
	//�M��Ă���Ƃ��̓_���[�W������
	if (m_IsWallowing) {
		damage *= 2.0f;
	}
	m_GameStatus.m_Energy -= damage;

	//�̗͖����Ȃ�����c�@������
	if (m_GameStatus.m_Energy < 0.0f) {
		m_GameStatus.m_Life--;
		if (m_GameStatus.m_Life <= 0) {
			m_IsGameOver = true;
		}
	}
}

void CM_ParameterSystem::BreakBlock(int count) {
	m_GameStatus.m_Score += 100 * count;
}

void CM_ParameterSystem::ObtainWarm() {
	//�~�~�Y�ő̗�20��
	m_GameStatus.m_Energy += 20.0f;
	if (m_GameStatus.m_Energy >= 101.0f) {
		m_GameStatus.m_Energy = 100.99f;
	}
}

void CM_ParameterSystem::GoForward() {
	if (m_GameStatus.m_DownDepth < m_StageParameter.m_Depth) {
		m_GameStatus.m_DownDepth++;
	} else
	if (m_GameStatus.m_UpDepth < m_StageParameter.m_Depth) {
		m_GameStatus.m_UpDepth++;
	}
	if (m_GameStatus.m_UpDepth < m_StageParameter.m_Depth) {
		return;
	}

	//�m�[�~�X�{�[�i�X
	if (m_GameStatus.m_Life >= 3) {
		m_GameStatus.m_Score += 500000;
	}
}

void CM_ParameterSystem::SetWallowSpring(bool isWallowing) {
	m_IsWallowing = isWallowing;
}

int CM_ParameterSystem::GetEnergy() {
	return (int)m_GameStatus.m_Energy;
}

int CM_ParameterSystem::GetLife() {
	return m_GameStatus.m_Life;
}

int CM_ParameterSystem::GetScore() {
	return m_GameStatus.m_Score;
}

int CM_ParameterSystem::GetRemainDepth() {
	if (m_GameStatus.m_DownDepth < m_StageParameter.m_Depth) {
		return m_StageParameter.m_Depth - m_GameStatus.m_DownDepth;
	}
	if (m_GameStatus.m_UpDepth < m_StageParameter.m_Depth) {
		return m_StageParameter.m_Depth - m_GameStatus.m_UpDepth;
	}
	return 0;
}
