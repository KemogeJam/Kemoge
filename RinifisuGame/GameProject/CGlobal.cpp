#include "CGlobal.h"

std::map<std::string, CImage>			CGlobal::m_Image;
std::map<std::string, TexturePacker>	CGlobal::m_Rect;

float CGlobal::m_Camera;

void CGlobal::Load_Image(std::string path)
{
	//‰æ‘œ‚Ì“Ç‚İ‚İ
	m_Image[path].Load(const_cast<char *>((path + ".png").c_str()));

	//‰æ‘œ‚ÌˆÊ’uî•ñ‚Ì“Ç‚İ‚İ
	m_Rect[path].Load(path + ".xml");
}

void CGlobal::Release_Image(std::string path)
{
	m_Image[path].Release();

	m_Image.erase(path);
}

const CImage & CGlobal::Get_Image(std::string path, std::string name)
{
	TextureRect rect = m_Rect[path][name];

	m_Image[path].setRect(rect.x, rect.y, rect.x + rect.w, rect.y + rect.h);
	m_Image[path].setSize(static_cast<float>(rect.w), static_cast<float>(rect.h));

	return m_Image[path];
}
