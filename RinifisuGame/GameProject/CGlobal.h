#pragma once

//�l�X�ȋ@�\
#include "Include.h"

//�ʃN���X�Ԃł���肪�K�v�ȕϐ�
class CGlobal
{
private:
	static std::map<std::string, CImage>		m_Image;	//�摜
	static std::map<std::string, TexturePacker>	m_Rect;		//�摜�͈�

public:
	static float								m_Camera;	//�J�����̈ʒu

public:
	static void Load_Image(std::string path);				//�摜�Ɖ摜�͈̓f�[�^�̓ǂݍ���
	static void Release_Image(std::string path);			//�摜�Ɖ摜�͈̓f�[�^�̉��

	static const CImage & Get_Image(std::string path, std::string name);		//�摜�̎擾
	static const TextureRect & Get_Rect(std::string path, std::string name);	//�摜�͈͂̎擾
	static const std::vector<TextureRect> & GetArray_Rect(std::string path, std::vector<std::string> name);	//�摜�͈͂̎擾
};

//�^�X�N�D�揇��
enum class EPriority
{
	//MainGame
	CM_Img_Test = 0,
	CM_Sys_GameMap,

	CM_Img_Block,

	CM_Img_Number,
	CM_Img_Player,
	CM_Img_GameMap,

	//���̑�
};