#pragma once
#include "Include.h"

class CTU_Background : public GameTask
{
private:
	CImage	m_Image;
	CFont	m_Font{ L"ƒƒCƒŠƒI", 50 };

public:
	CTU_Background();

protected:
	void Update();
	void Draw();
};
