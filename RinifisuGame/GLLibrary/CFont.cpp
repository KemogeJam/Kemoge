#include "CFont.h"
#include "CCamera.h"
#include <locale.h>

//コンストラクタ フォント作成
CFont::CFont(wchar_t *font, int size)
{
 Hfont = CreateFont(
        size,      //フォント高さ
        0,       //文字幅
        0,       //テキストの角度
        0,       //ベースラインとｘ軸との角度
        FW_REGULAR,     //フォントの太さ
        FALSE,      //イタリック体
        FALSE,      //アンダーライン
        FALSE,      //打ち消し線
        SHIFTJIS_CHARSET,   //文字セット
        OUT_DEFAULT_PRECIS,   //出力精度
        CLIP_DEFAULT_PRECIS,  //クリッピング精度
        ANTIALIASED_QUALITY,  //出力品質
        FIXED_PITCH | FF_MODERN, //ピッチとファミリー
        font);     //書体名

 Hdc = wglGetCurrentDC();
 SelectObject(Hdc, Hfont);
}

void CFont::Draw(int x,int y,float r,float g,float b,char *str)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	//スクリーン左上を原点(0,0)にした正射投影の行列を作成
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