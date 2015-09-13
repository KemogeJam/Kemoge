#pragma once
#include "Include.h"

class CTI_Background : public GameTask
{
private:
	CImage	m_Image;
public:
	CTI_Background();

protected:
	void Update();
	void Draw();
};
