#include <stdio.h>
#include <string.h>
#include "CXLoader.h"



/*
  ��s�ǂݍ���
*/
char str[255]="";
#define SCAN_DATA(fp,str,format,...) {	        \
	fgets(str,255,fp);							\
	sscanf_s(str,format,__VA_ARGS__);				\
}

/*
  �����񂩂�;"}{���폜
*/
static void cutSymbol(char *src,char *dst){
	while(*src) {
		if(*src != ' ' && *src != '}' && *src != '{' && *src != ';' && *src != '\"') *dst++=*src++;
		else src++;
	}
	*dst = '\0';
}

/*
  �g�[�N����ǂݍ���
*/
static void readToken(FILE *fp,char* token)
{
	char t[64]="";
	SCAN_DATA(fp,str,"%s",t,64);	
	cutSymbol(t,token);
}
/*
  �t�@�C������ǂݍ���
*/
bool CXLoader::load(char *filePath) {
	FILE *fp;
	fopen_s(&fp, filePath, "r");
	if(!fp) {
		printf("%s���J���܂���", filePath);
		return false;
	}
	char token[64];
	while(!feof(fp)){
		readToken(fp,token);
		if(strcmp(token,"Mesh")==0) {
			printf("%s�𔭌�",token);
		}
		if(strcmp(token,"MeshMaterialList")==0) {
			printf("%s�𔭌�",token);
		}
		if(strcmp(token,"Material")==0) {
			printf("%s�𔭌�",token);
		}
		if(strcmp(token,"MeshNormals")==0) {
			printf("%s�𔭌�",token);
		}
	}
	return true;
}