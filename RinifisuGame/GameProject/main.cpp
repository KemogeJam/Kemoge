#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#define FULL_SCREEN 0

#include "Include.h"

#include "CMainGame.h"
#include "CTitle.h"

CScene* g_Scene = new CScene();

ESceneChange g_Change;

void GameMain()
{
	//シーン更新
	g_Change = g_Scene->Update();

	//タスク更新
	GameTaskManager::Update();

	//カメラ行列更新
	glLoadMatrixf(CCamera::getCamera()->getMatrix().f);

	//シーンが空なら（ロード中なら）
	if (g_Change != ESceneChange::None)
	{
		
	}
	//そうでなければ描画
	else GameTaskManager::Draw();
}

void Display(void) {
	//各バッファーをクリア
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//行列の初期化
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GameMain();

	glutSwapBuffers();

	switch (g_Change)
	{
	case ESceneChange::None:

		break;

	case ESceneChange::Main:
		delete g_Scene;
		g_Scene = new CMainGame();
		break;

	case ESceneChange::Title:
		delete g_Scene;
		g_Scene = new CTitle();
		break;
	}
}

void Init(void)
{
	//フレーム制御初期化
	CFPS::Init();

	//ボタンの設定
	CInput::SetButton(0, CInput::eButton1, ' ');
	CInput::SetButton(0, CInput::eButton2, 'Q');
	CInput::SetButton(0, CInput::eButton3, 'E');
	CInput::SetButton(0, CInput::eUp, 'W');
	CInput::SetButton(0, CInput::eDown, 'S');
	CInput::SetButton(0, CInput::eLeft, 'A');
	CInput::SetButton(0, CInput::eRight, 'D');
	CInput::SetButton(0, CInput::eMouseL, MK_LBUTTON);
	CInput::SetButton(0, CInput::eMouseR, MK_RBUTTON);

	//カメラ初期化
	CCamera::getCamera()->LookAt(CVector3D(0, 2, 0), CVector3D(0, 2, 1), CVector3D(0.0, 1.0, 0.0));
}

void Resize(int w, int h)
{
	glViewport(0, 0, w, h);

	//カメラのサイズを設定（正投影用）
	CCamera::getCamera()->SetSize(1280, 960);

	//スクリーンサイズを設定（ビューポート用）
	CCamera::getCamera()->setScreenRect(CRect(0, 0, 1280, 960));

	//射影行列を設定
	CMatrix mProj;
	mProj.Perspective(Utility::DgreeToRadian(75.0f), static_cast<float>(w) / static_cast<float>(h), 1.0f, 1000.0f);
	CCamera::getCamera()->setProjectionMatrix(mProj);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(CCamera::getCamera()->getProjectionMatrix().f);
}

void Idle(void)
{
	CInput::UpDate();
	Display();

	CFPS::Wait();

	char title[32];
	sprintf_s(title, "Game - %dFPS", CFPS::getFPS());

	glutSetWindowTitle(title);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '\033':  // '\033' は ESC の ASCII コード
		glutDisplayFunc(NULL);
		glutKeyboardFunc(NULL);
		glutIdleFunc(NULL);
		glutReshapeFunc(NULL);
		Sleep(100);
		exit(0);
		break;

	default:
		break;
	}
}

void wheel(int wheel_number, int direction, int x, int y)
{
	CInput::addMouseWheel(direction);
}

int __main(int* argcp, char** argv)
{
	glutInit(argcp, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);

#if (FULL_SCREEN)
	glutGameModeString("640x480:32@60");
	glutEnterGameMode();
#else
	glutInitWindowSize(960, 720);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Game");
#endif

	glewInit();

	SetCurrentDirectory(L"data");

	glClearColor(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);//ブレンドの有効化
	//glEnable(GL_CULL_FACE);

	//固定シェーダー用
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	Init();

	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutIdleFunc(Idle);
	glutReshapeFunc(Resize);
	glutMouseWheelFunc(wheel);
	glutMainLoop();

	return 0;
}

INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR argv, INT )
{
	return __main(&__argc, __argv);
}

int main(int argc, char** argv)
{
	return __main(&argc, argv);
}