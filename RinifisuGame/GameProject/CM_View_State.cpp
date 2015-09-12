#include "CM_View_State.h"

CM_View_State::CM_View_State()
	: GameTask({ BIND(CM_View_State::Update) }, 10, 10)
{
	m_Image_Background = CGlobal::Get_Image("MainGame\\ViewState", "Background");
	m_Image_Background.getPos().x = 880;

	m_Image_Destination = CGlobal::Get_Image("MainGame\\ViewState", "MarkGround");
	m_Image_Destination.getPos().x = 880;
	m_Image_Destination.getPos().y = 170;

	for (int i = 0; i < DEPTH_NUMBER_MAX; i++) {
		//m_Images_Depth[i] = CGlobal::Get_Image("MainGame\\ViewState", "NumberLife" );
	}


}

void CM_View_State::Update()
{
}

void CM_View_State::Draw()
{
	m_Image_Background.Draw();
	m_Image_Destination.Draw();
	for (int i = 0; i < DEPTH_NUMBER_MAX; i++) {
		//m_Images_Depth[i].Draw();
	}

}

void UpdateDepthCount(int depth) {

}

void ChangeDepthType() {

}

void UpdatePts(int pts) {

}

void UpdateEnergy(int energy) {

}

void UpdateLife(int life) {

}