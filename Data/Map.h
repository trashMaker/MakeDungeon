#pragma once
#include <string>
#include <vector>
#include "Array2D.h"
class Map{
private:
	Array2D<char> mData;
	int width;
	int height;
	std::string mapName;

	struct POSITION{
		int x;
		int y;
	};
public:
	void readmap(const std::string& fileName, const std::string& format);
	POSITION getRandomCharctorIndex(const char charctor);
	inline const int getWidth()const throw(){
		return width;
	}
	inline const int getHeight()const throw(){
		return height;
	}
	inline const std::string& getMapName()const throw(){
		return mapName;
	}
	inline Array2D<char>& getData()throw(){
		return mData;
	}
	inline const Array2D<char>& getData()const throw(){
		return mData;
	}
	Map(const std::string& name, const int width = 0, const int height = 0, const char charctor = '#');
	Map(const std::string& fileName, const std::string& format = ".txt");
	Map(const Map& obj);
	Map& operator=(const Map& obj);
	virtual ~Map(){};

	void disp()const throw();
	////----------------------------------------------------------------
	//// 処理	配列の要素の参照を取得 書き込み用
	//// 引数	index0	第一インデックス
	//// 　　	index1	第二インデックス
	//// 返値	配列の要素の参照                operator
	////----------------------------------------------------------------
	//char& operator()(int x, int y) throw(){
	//	assert(0 <= x && x < width && "index0のサイズが入っていません");
	//	assert(0 <= y && y < height && "index1のサイズが入っていません");
	//	return mData(x, y);
	//}
	////----------------------------------------------------------------
	//// 処理	配列の要素の参照を取得 読み込み用
	//// 引数	index0	第一インデックス
	//// 　　	index1	第二インデックス
	//// 返値	配列の要素の参照
	////----------------------------------------------------------------
	//const char& operator()(int x, int y)const throw(){
	//	assert(0 <= x && x < width && "index0のサイズが入っていません");
	//	assert(0 <= y && y < height && "index1のサイズが入っていません");
	//	return mData(x, y);
	//}
};