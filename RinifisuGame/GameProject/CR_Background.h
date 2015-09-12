#pragma once
#include "Include.h"

class CR_Background : public GameTask
{
private:
	CImage	m_Image;
	CFont	m_Font{ L"���C���I", 50 };

public:
	CR_Background();

protected:
	void Update();
	void Draw();
};
