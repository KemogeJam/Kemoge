#include "CGlobal.h"

CImage			CGlobal::m_Image;
TexturePacker	CGlobal::m_Rect;

void CGlobal::Load_Image(std::string path)
{
	//�摜�̊J��
	m_Image.Release();

	//�摜�̓ǂݍ���
	m_Image.Load(const_cast<char *>((path + ".png").c_str()));

	//�摜�̈ʒu���̓ǂݍ���
	m_Rect.Load(path + ".xml");
}

const CImage & CGlobal::Get_Image(std::string name)
{
	TextureRect rect = m_Rect[name];

	m_Image.setRect(rect.x, rect.y, rect.x + rect.w, rect.y + rect.h);
	m_Image.setSize(static_cast<float>(rect.w), static_cast<float>(rect.h));

	return m_Image;
}
