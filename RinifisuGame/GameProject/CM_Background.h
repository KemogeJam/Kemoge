#pragma once
#include "Include.h"

//ƒƒCƒ“ƒQ[ƒ€‚Ì”wŒi‚Å‚·
class CM_Background : public GameTask
{
private:
	CImage m_ImageLeft;
	CImage m_ImageRight;
	CImage m_ImageBackground;

public:
	CM_Background();

protected:
	void Update();
	void Draw();
};