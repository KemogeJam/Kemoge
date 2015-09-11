//Copyright © 2015 Rinifisu
//http://rinifisu.blog.jp/

#include "TextManager.h"

#include <fstream>

std::string TextManager::Read(std::string path)
{
	//ファイル読み込み
	std::ifstream read(path);
	//失敗した場合は読み込まずに終了
	if (!read)
	{
		read.close();
		return "";
	}

	//文字を取得
	std::string tmp = "";
	std::string returnStr = "";
	while (read && std::getline(read, tmp))
	{
		returnStr += tmp;
	}

	read.close();

	return returnStr;
}

bool TextManager::Write(std::string path, std::string str)
{
	//ファイル書き込み
	std::ofstream write(path);
	//失敗した場合は書き込まずに終了
	if (!write)
	{
		write.close();
		return false;
	}

	//文字を書き込み
	write << str << std::endl;

	return true;
}