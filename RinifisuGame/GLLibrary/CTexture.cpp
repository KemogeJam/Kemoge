
#include "GL.h"
#include "glpng.h"
#include "CTexture.h"
#include "BmpFormat.h"
//#include "png.h"


//SDLインクルード（PNGファイル入力）
//#include "SDL_image.h"

CTexture::CTexture() : m_data(NULL),m_bufID(0){
}
CTexture::~CTexture() {
	Release();
}

bool CTexture::loadBmp(char *path){
	FILE *fp;
	fopen_s(&fp,path,"rb");
	BITMAPFILEHEADER header;
	BITMAPINFOHEADER info;
	fseek(fp,0,SEEK_SET);
	fread(&header,sizeof(BITMAPFILEHEADER),1,fp);
	
	fread(&info,sizeof(BITMAPINFOHEADER),1,fp);
	
	m_width = info.biWidth;
	m_height = info.biHeight;

	int w = (m_width*3);
	w= (w%4==0) ? w : (w/4)*4+1;

	//imgSize = info.biSizeImage;
	m_imgSize = header.bfSize - header.bfOffBits;
	m_data = new unsigned char[m_imgSize+4];
	for(int i=0;i<m_height;i++) {
		fread(&m_data[(m_height-i-1)*m_width*3],w,1,fp);

	}
	
	//fread(data,info.biSizeImage,1,fp);

	fclose(fp);

	m_internalFormat = GL_RGB;
	if(info.biBitCount==24) {
		m_format = GL_BGR_EXT;
	}else {
		delete[] m_data;
		return false;
	}
	
	
	glGenTextures(1,&m_bufID);
	glBindTexture(GL_TEXTURE_2D,m_bufID);
	glTexImage2D(GL_TEXTURE_2D,0,m_internalFormat,m_width,m_height,0,m_format,GL_UNSIGNED_BYTE,m_data);
	glBindTexture(GL_TEXTURE_2D,0);

	

	delete[] m_data;

	return true;
}

bool CTexture::loadPng(char *path){
	pngInfo info;
	m_bufID = pngBind (path, PNG_NOMIPMAP, PNG_ALPHA, &info, GL_CLAMP, GL_NEAREST, GL_NEAREST);
	if(m_bufID==0) return false;
	m_width = info.Width;
	m_height = info.Height;

	return true;

}
bool CTexture::Load(char *path){
	FILE* fp;
	fopen_s(&fp,path, "rb");
	if(!fp) {
		printf("ファイルが読み込めません[%s]",path);
		m_bufID=0;
		return false;
	}
	unsigned char crc[4];
	fread(crc,4,1,fp);
	if(crc[0]==0x42 && crc[1]==0x4D) {
		fclose(fp);
		return loadBmp(path);
	}else {
//	if(crc[1]==0x50 && crc[2]==0x4E && crc[3]==0x47) {
		fclose(fp);
		return loadPng(path);
	}
	
	
}
void CTexture::MapTexture() {
	
	if(m_bufID==-1) return;
	//glRasterPos2f(-1.0f,-1.0f);
	glBindTexture(GL_TEXTURE_2D,m_bufID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	

	glEnable(GL_TEXTURE_2D);
}

void CTexture::UnmapTexture() {
	if(m_bufID==-1) return;
	glBindTexture(GL_TEXTURE_2D,0);
	glDisable(GL_TEXTURE_2D);
}
void CTexture::Draw( void )
{
	glRasterPos2f(0.0f,0.0f);
	glDrawPixels(m_width,m_height,m_format,GL_UNSIGNED_BYTE,m_data);
};

void CTexture::Release() {
	if(m_bufID!=0)
		glDeleteTextures(1,&m_bufID);
}