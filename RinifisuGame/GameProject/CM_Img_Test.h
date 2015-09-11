#pragma once
#include "Include.h"

class CM_Img_Test : public GameTask
{
private:
	CImage	m_Image;

	CFont	m_Font { L"ƒƒCƒŠƒI", 50 };

public:
	CM_Img_Test();

protected:
	void Update();
	void Draw();
};