#include "CharacterImage.h"

CharacterImage::CharacterImage() {
	m_Image = CGlobal::Get_Image("MainGame\\Character", "Img");

	m_AnimationRect = TextureRect{ 400, 400, 80, 80 };
	int size = 100;
	//�A�C�h����
	{
		int origin = 0;
		AnimationDetail detail = AnimationDetail{};
		{
			CVector2D pos = CVector2D(origin, 0);
			detail.m_Positions.push_back(pos);
		}
		{
			CVector2D pos = CVector2D(origin + size, 0);
			detail.m_Positions.push_back(pos);
		}
		{
			CVector2D pos = CVector2D(origin, 0);
			detail.m_Positions.push_back(pos);
		}
		{
			CVector2D pos = CVector2D(origin + size * 2, 0);
			detail.m_Positions.push_back(pos);
		}
		detail.m_Size = CVector2D{ 100.0f, 100.0f };
		detail.m_IsLoop = true;
		detail.m_ComaPerFrame = 0.2f;
		add(detail);
	}

	//�A�C�h���E
	{
		int origin = 300;
		AnimationDetail detail = AnimationDetail{};
		{
			CVector2D pos = CVector2D(origin, 0);
			detail.m_Positions.push_back(pos);
		}
		{
			CVector2D pos = CVector2D(origin + size, 0);
			detail.m_Positions.push_back(pos);
		}
		{
			CVector2D pos = CVector2D(origin, 0);
			detail.m_Positions.push_back(pos);
		}
		{
			CVector2D pos = CVector2D(origin + size * 2, 0);
			detail.m_Positions.push_back(pos);
		}
		detail.m_Size = CVector2D{ 100.0f, 100.0f };
		detail.m_IsLoop = true;
		detail.m_ComaPerFrame = 0.2f;
		add(detail);
	}


	//�@�鍶
	{
		int origin = 900;
		AnimationDetail detail = AnimationDetail{};
		{
			CVector2D pos = CVector2D(origin, 0);
			detail.m_Positions.push_back(pos);
		}
		{
			CVector2D pos = CVector2D(origin + size, 0);
			detail.m_Positions.push_back(pos);
		}
		{
			CVector2D pos = CVector2D(origin + size * 2, 0);
			detail.m_Positions.push_back(pos);
		}
		detail.m_Size = CVector2D{ 100.0f, 100.0f };
		detail.m_IsLoop = true;
		detail.m_ComaPerFrame = 0.2f;
		add(detail);
	}
	//�@��E
	{
		int origin = 1200;
		AnimationDetail detail = AnimationDetail{};
		{
			CVector2D pos = CVector2D(origin, 0);
			detail.m_Positions.push_back(pos);
		}
		{
			CVector2D pos = CVector2D(origin + size, 0);
			detail.m_Positions.push_back(pos);
		}
		{
			CVector2D pos = CVector2D(origin + size * 2, 0);
			detail.m_Positions.push_back(pos);
		}
		detail.m_Size = CVector2D{ 100.0f, 100.0f };
		detail.m_IsLoop = true;
		detail.m_ComaPerFrame = 0.2f;
		add(detail);
	}
	//�@�鉺
	{
		int origin = 1500;
		AnimationDetail detail = AnimationDetail{};
		{
			CVector2D pos = CVector2D(origin, 0);
			detail.m_Positions.push_back(pos);
		}
		{
			CVector2D pos = CVector2D(origin + size, 0);
			detail.m_Positions.push_back(pos);
		}
		{
			CVector2D pos = CVector2D(origin + size * 2, 0);
			detail.m_Positions.push_back(pos);
		}
		detail.m_Size = CVector2D{ 100.0f, 100.0f };
		detail.m_IsLoop = true;
		detail.m_ComaPerFrame = 0.2f;
		add(detail);
	}
	//�@���
	{
		int origin = 1800;
		AnimationDetail detail = AnimationDetail{};
		{
			CVector2D pos = CVector2D(origin, 0);
			detail.m_Positions.push_back(pos);
		}
		{
			CVector2D pos = CVector2D(origin + size, 0);
			detail.m_Positions.push_back(pos);
		}
		{
			CVector2D pos = CVector2D(origin + size * 2, 0);
			detail.m_Positions.push_back(pos);
		}
		detail.m_Size = CVector2D{ 100.0f, 100.0f };
		detail.m_IsLoop = true;
		detail.m_ComaPerFrame = 0.2f;
		add(detail);
	}
	//������
	{
		int origin = 2100;
		AnimationDetail detail = AnimationDetail{};
		{
			CVector2D pos = CVector2D(origin, 0);
			detail.m_Positions.push_back(pos);
		}
		{
			CVector2D pos = CVector2D(origin + size, 0);
			detail.m_Positions.push_back(pos);
		}
		detail.m_Size = CVector2D{ 100.0f, 100.0f };
		detail.m_IsLoop = true;
		detail.m_ComaPerFrame = 0.2f;
		add(detail);
	}
	//�����E
	{
		int origin = 2300;
		AnimationDetail detail = AnimationDetail{};
		{
			CVector2D pos = CVector2D(origin, 0);
			detail.m_Positions.push_back(pos);
		}
		{
			CVector2D pos = CVector2D(origin + size, 0);
			detail.m_Positions.push_back(pos);
		}
		detail.m_Size = CVector2D{ 100.0f, 100.0f };
		detail.m_IsLoop = true;
		detail.m_ComaPerFrame = 0.2f;
		add(detail);
	}

	m_NowPlayAnimationId = EAnimationId::E_IdleLeft;
}

void CharacterImage::Update() {
	AnimationImage::Update();
}

void CharacterImage::Draw() {
	AnimationImage::Draw();
}