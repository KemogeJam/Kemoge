#include "TexturePacker.h"

TextureRect::TextureRect()
	: x(0), y(0), w(0), h(0)
{

}

TextureRect::TextureRect(int _x, int _y, int _w, int _h)
	: x(_x), y(_y), w(_w), h(_h)
{

}

TexturePacker::TexturePacker()
{

}

TexturePacker::TexturePacker(std::string path)
{
	Load(path);
}

void TexturePacker::Load(std::string path)
{
	//消去
	m_List.clear();

	//読み込み
	std::string data = TextManager::Read(path);

	//検索内容
	std::string search[] = { "name=\"", "x=\"", "y=\"", "width=\"", "height=\"" };

	//検索先頭位置
	unsigned int index = 0;

	//終了フラグが立つまでループ
	for (bool flag = true; flag;)
	{
		std::string tag = "";
		TextureRect rect;

		//各項目を検索
		for (int item = 0; item < 5; item++)
		{
			//文字の検索
			unsigned int pos = data.find(search[item], index);

			//文字がヒットしたら
			if (pos != std::string::npos)
			{
				//検索開始位置を今の場所に設定
				index = pos + search[item].size();

				//文字の検索
				unsigned int strSize = data.find("\"", index);

				//内容の取得
				std::string getStr = data.substr(index, strSize - index);

				//printf("%s\n", getStr.c_str());

				//内容を代入
				switch (item)
				{
				case 0:
					tag = getStr;
					break;

				case 1:
					rect.x = std::stoi(getStr);
					break;

				case 2:
					rect.y = std::stoi(getStr);
					break;

				case 3:
					rect.w = std::stoi(getStr);
					break;

				case 4:
					rect.h = std::stoi(getStr);
					break;
				}
			}
			//ヒットしなければ終了
			else
			{
				flag = false;
				break;
			}
		}

		//データの追加
		if (flag) m_List[tag] = rect;
	}
}

TextureRect TexturePacker::operator[](std::string tag)
{
	return m_List[tag];
}