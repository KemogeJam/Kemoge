#pragma once

//�l�X�ȋ@�\
#include "Include.h"

//�ʃN���X�Ԃł���肪�K�v�ȕϐ�
class CGlobal
{
private:
	static CImage			m_Image;	//�摜
	static TexturePacker	m_Rect;		//�摜�͈�

public:
	static void Load_Image(std::string path);			//�摜�Ɖ摜�͈̓f�[�^�̓ǂݍ���

	static const CImage & Get_Image(std::string name);	//�摜�̎擾
};

//�^�X�N�D�揇��
enum class EPriority
{
	//MainGame
	CM_Img_Test = 0,

	//���̑�
};