#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include <sstream>
#include "Exception.h"

//オレオレAssert(名づけおｋっや:noob)
#define ASSERT(EXPRESSION,DATA,DATANAME,MESSAGE) \
	mockAssert(EXPRESSION, DATA, DATANAME, MESSAGE, __FILE__, __FUNCTION__, __LINE__)
//文字列変換
#define STRING(str) #str

const std::string concatenate(const std::string& fileName, const std::string& format);

int getRandom(int min, int max);

std::vector<int> getRandomTable(int randMin, int randMax);
void setRandomTable(std::vector<int>* randNumber, int rand);

void logErrorCout(const exception::Exception& ex);
void logErrorOutput(const exception::Exception& ex);

int parseProperty(const std::vector<std::string>& data, const char* propertyName);

std::vector<std::string> readFileData(const std::string& file, const std::string& format);


//マクロを展開した先にdata変数がローカルで宣言されていたりすると、おかしなことになったりする。
//template<typename type>
//void mockAssert(const int expression, const type data, const std::string& dataName, const std::string& message, const std::string& argFile, const std::string& argFunction, const int argLine);
template<typename type>
void mockAssert(const int expression, const type data, const std::string& dataName, const std::string& message, const std::string& argFile, const std::string& argFunction, const int argLine){

	if (expression == 0){
		std::ostringstream outputStr;
		outputStr << "errorn情報:" << dataName << std::endl;
		outputStr << "mesage:" << message << std::endl;
		outputStr << "errorn数値:" << data << std::endl;
		outputStr << "Assertion failed:" << expression << std::endl;
		outputStr << "file" << argFile << std::endl;
		outputStr << "function" << argFunction << std::endl;
		outputStr << "line" << argLine << std::endl;
		MessageBoxA(NULL, outputStr.str().c_str(), "メッセージ", MB_OK);
	}
}

