//TexturePacker
//https://www.codeandweb.com/texturepacker

#pragma once

#include <map>
#include <vector>
#include "TextManager.h"

class TextureRect
{
public:
	int x;
	int y;
	int w;
	int h;

public:
	TextureRect();
	TextureRect(int _x, int _y, int _w, int _h);
};

class TexturePacker
{
private:
	std::map<std::string, TextureRect> m_List;

public:
	TexturePacker();
	TexturePacker(std::string path);

	//TexturePacker の Sparrow / Starling で 出力したスプライトシートデータを読み込む
	void Load(std::string path);

	//データの取得
	TextureRect operator[](std::string tag);
};