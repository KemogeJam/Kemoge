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
	//����
	m_List.clear();

	//�ǂݍ���
	std::string data = TextManager::Read(path);

	//�������e
	std::string search[] = { "name=\"", "x=\"", "y=\"", "width=\"", "height=\"" };

	//�����擪�ʒu
	unsigned int index = 0;

	//�I���t���O�����܂Ń��[�v
	for (bool flag = true; flag;)
	{
		std::string tag = "";
		TextureRect rect;

		//�e���ڂ�����
		for (int item = 0; item < 5; item++)
		{
			//�����̌���
			unsigned int pos = data.find(search[item], index);

			//�������q�b�g������
			if (pos != std::string::npos)
			{
				//�����J�n�ʒu�����̏ꏊ�ɐݒ�
				index = pos + search[item].size();

				//�����̌���
				unsigned int strSize = data.find("\"", index);

				//���e�̎擾
				std::string getStr = data.substr(index, strSize - index);

				//printf("%s\n", getStr.c_str());

				//���e����
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
			//�q�b�g���Ȃ���ΏI��
			else
			{
				flag = false;
				break;
			}
		}

		//�f�[�^�̒ǉ�
		if (flag) m_List[tag] = rect;
	}
}

TextureRect TexturePacker::operator[](std::string tag)
{
	return m_List[tag];
}