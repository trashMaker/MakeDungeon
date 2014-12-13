#include <fstream>
#include <iostream>

#include "map.h"
#include "Common.h"
Map::Map(const std::string& name, int argWidth, int argHeight, const char charctor) :
mapName(name), width(argWidth), height(argHeight){
	ASSERT(argWidth > 0, argWidth, STRING(argWidth), "argWidth�ɓK�؂Ȓl�������Ă��܂���");
	ASSERT(argHeight > 0, argHeight, STRING(argHeight), "argHeight�ɓK�؂Ȓl�������Ă��܂���");
	ASSERT(0x20 < charctor && charctor < 0xE0, charctor, STRING(charctor), "�����Ă镶���������R�[�h�̕\�O�ł�");

	mData.setSize(width, height);

	for (int y = 0; y < height; ++y){
		for (int x = 0; x < width; ++x){
			mData(x, y) = charctor;
		}
	}
}
//-----------------------------------
//���� �R���X�g���N�^:�f�[�^�����o��.txt�̃}�b�v�`�b�v�̒ǉ�
//���� fileName 
//�@�@ format	.txt	
//�Ԓl none 
//-----------------------------------
Map::Map(const std::string& fileName, const std::string& format) :
mapName(fileName){
	if (fileName.size() == 0)THROW_EXCEPTION(exception::Exception, "�t�@�C���������݂��܂���");

	readmap(fileName, format);
}
//-----------------------------------
//���� MapChip�̃f�[�^��ǂݍ��݃f�[�^�����o��.txt�̃}�b�v�`�b�v�̒ǉ�
//���� fileName 
//�@�@ format	.txt	
//�Ԓl none 
//-----------------------------------
void Map::readmap(const std::string& fileName, const std::string& format){
	std::string test = "../MapChip/";
	std::string file = test;
	file += concatenate(fileName, format);

	//�t�@�C���ǂݍ���
	std::ifstream inputFile(file, std::ios_base::in);

	if (inputFile.fail()){
		THROW_EXCEPTION(exception::Exception, "�t�@�C�����J���܂���");
	}

	int x, y, maxX, maxY;
	maxX = maxY = 0;
	x = 0, y = 1;

	std::vector<std::string> data;
	std::string str;

	while (getline(inputFile, str, '\n')){
		data.push_back(str);
		x = str.size();
		if (x > maxX){ maxX = x; }
		str.clear();
	}
	maxY = data.size();

	ASSERT(maxX > 0, maxX, STRING(maxX), "maxX�ɓK�؂Ȓl�������Ă��܂���");
	ASSERT(maxY > 0, maxY, STRING(maxY), "maxY�ɓK�؂Ȓl�������Ă��܂���");

	mData.setSize(maxX, maxY);
	width = maxX;
	height = maxY;

	for (int y = 0; y < data.size(); ++y){
		for (int x = 0; x < data.at(y).size(); ++x){
			mData(x, y) = data.at(y).at(x);
		}
	}
	inputFile.close();
}
//-----------------------------------
//���� �R�s�[�R���X�g���N�^ *�g���Ė����̂ŃR�s�[
//���� obj 	
//�Ԓl none 
//-----------------------------------
Map::Map(const Map& obj){
	mapName = obj.getMapName();
	width = obj.getWidth();
	height = obj.getHeight();

	mData.setSize(width, height);

	for (int y = 0; y < height; ++y){
		for (int x = 0; x < width; ++x){
			mData(x, y) = obj.getData()(x, y);
		}
	}
}
//-----------------------------------
//���� ������Z�q *�g���Ė����̂ŃR�s�[
//���� obj 	
//�Ԓl none 
//-----------------------------------
Map& Map::operator=(const Map& obj){
	if (this != &obj){
		mapName = obj.getMapName();
		width = obj.getWidth();
		height = obj.getHeight();

		mData.setSize(width, height);

		for (int y = 0; y < height; ++y){
			for (int x = 0; x < width; ++x){
				mData(x, y) = obj.getData()(x, y);
			}
		}
	}
	return *this;
}
//-----------------------------------
//���� charctor�f�[�^���|�W�V�����������_���őI��ŕԂ�
//���� charctor 	�ǂ̃f�[�^��
//�Ԓl none 
//-----------------------------------
Map::POSITION Map::getRandomCharctorIndex(const char charctor){
	int charctorNum = mData.getCharctorCount(charctor);
	int count = getRandom(0, charctorNum - 1);

	POSITION temp;

	for (int y = 0; y < height; ++y){
		for (int x = 0; x < width; ++x){
			if (mData(x, y) == charctor){
				if (count == 0){
					temp.x = x;
					temp.y = y;
					return temp;
				}
				--count;
			}
		}
	}
	temp.x = -1;
	temp.y = -1;
	ASSERT(temp.x != -1, temp.x, STRING(temp.x), "temp.x�ɓK�؂Ȓl�������Ă��܂���");
	return temp;
}

//-----------------------------------
//���� �o�́@�f�o�b�O�p		
//�Ԓl none
//-----------------------------------
void Map::disp()const throw(){
	for (int y = 0; y < height; ++y){
		
		for (int x = 0; x < width; ++x){
			//std::cout << mData.at(y * width + x);

			switch (mData(x, y)){
			case '#':
				std::cout << "��";
				break;
			case 'c':
				std::cout << "��";
				break;
			case 't':
				std::cout << "��";
				break;
			default:
				std::cout << "�@";
			}
		}
		std::cout << std::endl;
	}
}