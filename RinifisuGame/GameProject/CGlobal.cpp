#include "CGlobal.h"

CImage			CGlobal::m_Image;
TexturePacker	CGlobal::m_Rect;

void CGlobal::Load_Image(std::string path)
{
	//画像の開放
	m_Image.Release();

	//画像の読み込み
	m_Image.Load(const_cast<char *>((path + ".png").c_str()));

	//画像の位置情報の読み込み
	m_Rect.Load(path + ".xml");
}

const CImage & CGlobal::Get_Image(std::string name)
{
	TextureRect rect = m_Rect[name];

	m_Image.setRect(rect.x, rect.y, rect.x + rect.w, rect.y + rect.h);
	m_Image.setSize(static_cast<float>(rect.w), static_cast<float>(rect.h));

	return m_Image;
}
