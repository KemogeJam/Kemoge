#pragma once
#pragma once
#include "Include.h"

//â∑êÚÇÃï\é¶Ç≈Ç∑
class CM_Spring : public GameTask
{
private:
	CImage m_ImageSpring;

public:
	CM_Spring();

protected:
	void Update();
	void Draw();
};