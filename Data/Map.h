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
	//// ����	�z��̗v�f�̎Q�Ƃ��擾 �������ݗp
	//// ����	index0	���C���f�b�N�X
	//// �@�@	index1	���C���f�b�N�X
	//// �Ԓl	�z��̗v�f�̎Q��                operator
	////----------------------------------------------------------------
	//char& operator()(int x, int y) throw(){
	//	assert(0 <= x && x < width && "index0�̃T�C�Y�������Ă��܂���");
	//	assert(0 <= y && y < height && "index1�̃T�C�Y�������Ă��܂���");
	//	return mData(x, y);
	//}
	////----------------------------------------------------------------
	//// ����	�z��̗v�f�̎Q�Ƃ��擾 �ǂݍ��ݗp
	//// ����	index0	���C���f�b�N�X
	//// �@�@	index1	���C���f�b�N�X
	//// �Ԓl	�z��̗v�f�̎Q��
	////----------------------------------------------------------------
	//const char& operator()(int x, int y)const throw(){
	//	assert(0 <= x && x < width && "index0�̃T�C�Y�������Ă��܂���");
	//	assert(0 <= y && y < height && "index1�̃T�C�Y�������Ă��܂���");
	//	return mData(x, y);
	//}
};