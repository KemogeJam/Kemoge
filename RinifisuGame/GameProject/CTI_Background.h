#pragma once
#include "Include.h"

class CTI_Background : public GameTask
{
private:
	CImage	m_Image;
	CFont	m_Font{ L"���C���I", 50 };

public:
	CTI_Background();

protected:
	void Update();
	void Draw();
};
