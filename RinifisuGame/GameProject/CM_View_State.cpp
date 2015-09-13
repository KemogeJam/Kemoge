#include "CM_View_State.h"

CM_View_State::CM_View_State()
	: GameTask({ BIND(CM_View_State::Update) }, 10, 10)
{
	m_Image_Background = CGlobal::Get_Image("MainGame\\ViewState", "Background");
	m_Image_Background.getPos().x = 880;

	m_Image_Destination = CGlobal::Get_Image("MainGame\\ViewState", "MarkSpring");
	m_Image_Destination.getPos().x = 880;
	m_Image_Destination.getPos().y = 170;

	m_Image_GaugeFrame = CGlobal::Get_Image("MainGame\\ViewState", "GaugeFrame");
	m_Image_GaugeFrame.getPos().x = 900;
	m_Image_GaugeFrame.getPos().y = 670;

	m_Image_GaugeBackground = CGlobal::Get_Image("MainGame\\ViewState", "GaugeBackground");
	m_Image_GaugeBackground.getPos().x = m_Image_GaugeFrame.getPos().x + 4;
	m_Image_GaugeBackground.getPos().y = m_Image_GaugeFrame.getPos().y + 4;

	m_Image_Face = CGlobal::Get_Image("MainGame\\ViewState", "Face");
	m_Image_Face.getPos().x = 900;
	m_Image_Face.getPos().y = 800;

	UpdateDepthCount(0);
	UpdatePts(0);
	UpdateEnergy(100);
	UpdateLife(0);
}

void CM_View_State::Update()
{
}

void CM_View_State::Draw()
{
	m_Image_Background.Draw();
	m_Image_Destination.Draw();
	for (int i = 0; i < DEPTH_NUMBER_MAX; i++) {
		m_Images_Depth[i].Draw();
	}
	for (int i = 0; i < PTS_NUMBER_MAX; i++) {
		m_Images_Pts[i].Draw();
	}
	m_Image_GaugeBackground.Draw();
	m_Image_GaugeRed.Draw();
	m_Image_GaugeYellow.Draw();
	m_Image_GaugeGreen.Draw();
	m_Image_GaugeFrame.Draw();

	m_Image_Face.Draw();
	m_Image_Life.Draw();
}

void CM_View_State::UpdateDepthCount(int depth) {

	for (int i = 0; i < DEPTH_NUMBER_MAX; i++) {
		char names[16];
		char name[16];
		sprintf(names, "%4d", depth);
		sprintf(name, "Pts%c", names[i]);

		m_Images_Depth[i] = CGlobal::Get_Image("MainGame\\ViewState", name);
		CImage &image = m_Images_Depth[i];
		image.getPos().x = 925 + 78 * i;
		image.getPos().y = 290;
	}
}

void CM_View_State::ChangeDepthType() {

}

void CM_View_State::UpdatePts(int pts) {
	for (int i = 0; i < PTS_NUMBER_MAX; i++) {
		char names[16];
		char name[16];
		sprintf(names, "%7d", pts);
		sprintf(name, "Pts%c", names[i]);

		m_Images_Pts[i] = CGlobal::Get_Image("MainGame\\ViewState", name);
		CImage &image = m_Images_Pts[i];
		image.getPos().x = 900 + 51 * i;
		image.getPos().y = 490;
	}
}

void CM_View_State::UpdateEnergy(int energy) {
	float percent = (float)energy / 100.0f;
	m_Image_GaugeRed = CGlobal::Get_Image("MainGame\\ViewState", "GaugeRed");
	m_Image_GaugeRed.getPos().x = m_Image_GaugeFrame.getPos().x + 4;
	m_Image_GaugeRed.getPos().y = m_Image_GaugeFrame.getPos().y + 4;
	m_Image_GaugeRed.setSize(m_Image_GaugeBackground.getSize().x * percent, m_Image_GaugeRed.getSize().y);

	m_Image_GaugeYellow = CGlobal::Get_Image("MainGame\\ViewState", "GaugeYellow");
	m_Image_GaugeYellow.getPos().x = m_Image_GaugeFrame.getPos().x + 4;
	m_Image_GaugeYellow.getPos().y = m_Image_GaugeFrame.getPos().y + 4;
	m_Image_GaugeYellow.setSize(m_Image_GaugeBackground.getSize().x * percent, m_Image_GaugeYellow.getSize().y);
	if (energy < 20) {
		m_Image_GaugeYellow.setColor(1.0f, 1.0f, 1.0f, 0.0f);
	}
	else {
		m_Image_GaugeYellow.setColor(1.0f, 1.0f, 1.0f, 1.0f);
	}

	m_Image_GaugeGreen = CGlobal::Get_Image("MainGame\\ViewState", "GaugeGreen");
	m_Image_GaugeGreen.getPos().x = m_Image_GaugeFrame.getPos().x + 4;
	m_Image_GaugeGreen.getPos().y = m_Image_GaugeFrame.getPos().y + 4;
	m_Image_GaugeGreen.setSize(m_Image_GaugeBackground.getSize().x * percent, m_Image_GaugeGreen.getSize().y);
	if (energy < 50) {
		m_Image_GaugeGreen.setColor(1.0f, 1.0f, 1.0f, 0.0f);
	}
	else {
		m_Image_GaugeGreen.setColor(1.0f, 1.0f, 1.0f, 1.0f);
	}

}

void CM_View_State::UpdateLife(int life) {
	char name[16];
	sprintf(name, "Per%d", life);
	m_Image_Life = CGlobal::Get_Image("MainGame\\ViewState", name);
	m_Image_Life.getPos().x = 900 + 100;
	m_Image_Life.getPos().y = 800;
	m_Image_Life.setSize(100, 100);
}