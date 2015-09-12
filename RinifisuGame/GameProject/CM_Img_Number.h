#pragma once
#include "Include.h"

class CM_Img_Number : public GameTask
{
private:
	CImage						m_Image;		//�摜�f�[�^
	std::vector<TextureRect>	m_RectArray;	//���l�f�[�^

	bool						m_RightShift;	//���l�`�掞�̃V�t�g����
	float						m_ShiftSpace;	//���l�Ԃ̃X�y�[�X

	EasingManager				m_Easing;		//�l�ړ�

public:
	CM_Img_Number(CVector2D position, bool rightShift);

	void SetNumber(double number, bool easing);
	void AddNumber(double number, bool easing);

	int GetNumber_Int();
	double GetNumber_Double();

protected:
	void Update();
	void Draw();
};