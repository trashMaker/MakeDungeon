#include <fstream>
#include <iostream>

#include "map.h"
#include "Common.h"
Map::Map(const std::string& name, int argWidth, int argHeight, const char charctor) :
mapName(name), width(argWidth), height(argHeight){
	ASSERT(argWidth > 0, argWidth, STRING(argWidth), "argWidthに適切な値が入っていません");
	ASSERT(argHeight > 0, argHeight, STRING(argHeight), "argHeightに適切な値が入っていません");
	ASSERT(0x20 < charctor && charctor < 0xE0, charctor, STRING(charctor), "入ってる文字が文字コードの表外です");

	mData.setSize(width, height);

	for (int y = 0; y < height; ++y){
		for (int x = 0; x < width; ++x){
			mData(x, y) = charctor;
		}
	}
}
//-----------------------------------
//処理 コンストラクタ:データメンバの.txtのマップチップの追加
//引数 fileName 
//　　 format	.txt	
//返値 none 
//-----------------------------------
Map::Map(const std::string& fileName, const std::string& format) :
mapName(fileName){
	if (fileName.size() == 0)THROW_EXCEPTION(exception::Exception, "ファイル名が存在しません");

	readmap(fileName, format);
}
//-----------------------------------
//処理 MapChipのデータを読み込みデータメンバの.txtのマップチップの追加
//引数 fileName 
//　　 format	.txt	
//返値 none 
//-----------------------------------
void Map::readmap(const std::string& fileName, const std::string& format){
	std::string test = "../MapChip/";
	std::string file = test;
	file += concatenate(fileName, format);

	//ファイル読み込み
	std::ifstream inputFile(file, std::ios_base::in);

	if (inputFile.fail()){
		THROW_EXCEPTION(exception::Exception, "ファイルが開けません");
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

	ASSERT(maxX > 0, maxX, STRING(maxX), "maxXに適切な値が入っていません");
	ASSERT(maxY > 0, maxY, STRING(maxY), "maxYに適切な値が入っていません");

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
//処理 コピーコンストラクタ *使って無いのでコピー
//引数 obj 	
//返値 none 
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
//処理 代入演算子 *使って無いのでコピー
//引数 obj 	
//返値 none 
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
//処理 charctorデータをポジションをランダムで選んで返す
//引数 charctor 	どのデータか
//返値 none 
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
	ASSERT(temp.x != -1, temp.x, STRING(temp.x), "temp.xに適切な値が入っていません");
	return temp;
}

//-----------------------------------
//処理 出力　デバッグ用		
//返値 none
//-----------------------------------
void Map::disp()const throw(){
	for (int y = 0; y < height; ++y){
		
		for (int x = 0; x < width; ++x){
			//std::cout << mData.at(y * width + x);

			switch (mData(x, y)){
			case '#':
				std::cout << "■";
				break;
			case 'c':
				std::cout << "★";
				break;
			case 't':
				std::cout << "通";
				break;
			default:
				std::cout << "　";
			}
		}
		std::cout << std::endl;
	}
}