//Copyright © 2015 Rinifisu
//http://rinifisu.blog.jp/

#pragma once

#include <string>
#include <vector>

class TextManager
{
public:
	static std::string Read(std::string path);
	static bool Write(std::string path, std::string str);
};