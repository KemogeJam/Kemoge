#include "CFont.h"
#include "CCamera.h"
#include <locale.h>

//�R���X�g���N�^ �t�H���g�쐬
CFont::CFont(wchar_t *font, int size)
{
 Hfont = CreateFont(
        size,      //�t�H���g����
        0,       //������
        0,       //�e�L�X�g�̊p�x
        0,       //�x�[�X���C���Ƃ����Ƃ̊p�x
        FW_REGULAR,     //�t�H���g�̑���
        FALSE,      //�C�^���b�N��
        FALSE,      //�A���_�[���C��
        FALSE,      //�ł�������
        SHIFTJIS_CHARSET,   //�����Z�b�g
        OUT_DEFAULT_PRECIS,   //�o�͐��x
        CLIP_DEFAULT_PRECIS,  //�N���b�s���O���x
        ANTIALIASED_QUALITY,  //�o�͕i��
        FIXED_PITCH | FF_MODERN, //�s�b�`�ƃt�@�~���[
        font);     //���̖�

 Hdc = wglGetCurrentDC();
 SelectObject(Hdc, Hfont);
}

void CFont::Draw(int x,int y,float r,float g,float b,char *str)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	//�X�N���[����������_(0,0)�ɂ������˓��e�̍s����쐬
	CMatrix	mProj = CMatrix(
		2.0f/CCamera::getCurrent()->getWhidth() , 0.0f, 0.0f, -1.0f,
         0.0f, -2.0f/CCamera::getCurrent()->getHeight() , 0.0f, 1.0f,
         0.0f, 0.0f, 1.0f, 0.0f,
         0.0f, 0.0f, 0.0f, 1.0f
     );
	glLoadMatrixf(mProj.f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();



	
	glColor4f(r, g, b, 1.0f);
	float font_color[]={r,g,b,1.0};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, font_color);
	glRasterPos2i(x, y);
	glDisable(GL_LIGHTING);
	
	setlocale(LC_CTYPE,"jpn");
	int size = _mbstrlen(str);
	wchar_t *buf=new wchar_t[size+1];

	MultiByteToWideChar(CP_ACP,0,str,-1,buf,sizeof(wchar_t)*size+1);

	int list = glGenLists(size);
	for( int i=0; i<size; i++ ){
		wglUseFontBitmapsW(Hdc, buf[i], 1, list + i);
	}
	for( int i=0; i<size; i++ ){
		glCallList(list + i);
	}
	glDeleteLists(list, size);

	delete buf;





	
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	

	glEnable(GL_LIGHTING);

};

void CFont::Release() {
	if( Hfont ) DeleteObject( Hfont );
}