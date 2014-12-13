#include "Common.h"
#include <random>
#include <fstream>
#include <iostream>
#include <regex>
#include <assert.h>
#include <vector>
#include <atlstr.h>

//-----------------------------------
//処理 文字連結
//引数 fileName 
//　　 format		
//返値 string 連結後の文字列
//-----------------------------------
const std::string concatenate(const std::string& fileName, const std::string& format){

	std::string str = fileName + format;

	return str;
}
//-----------------------------------
//処理 ランダム取得
//引数 min 最小
//　　 max 最大
//返値 int ランダム取得
//-----------------------------------
int getRandom(int min, int max){
	std::mt19937 rng{ std::random_device()() };
	std::uniform_int_distribution<int> dist(min, max);
	return dist(rng);
}
//-----------------------------------
//処理 ランダムテーブルのテーブルが最大になるまで取得
//引数 randMin 取得値の最小
//　　 randMax 取得値の最大
//　　 tableNum テーブルの数
//返値 vector<int> ランダムテーブル取得
//-----------------------------------
std::vector<int> getRandomTable(int randMin, int randMax){
	int tableNum = (randMax + 1) - randMin;
	std::vector<int> randNumber;
	//比較用に0番目に値追加
	randNumber.push_back(getRandom(randMin, randMax));

	while (randNumber.size() != tableNum){
		int rand = getRandom(randMin, randMax);
		setRandomTable(&randNumber, rand);
	}
	return randNumber;
}
//-----------------------------------
//処理 ランダムテーブルに追加
//引数 randNumber vector<int>*最小
//　　 rand ランダムで取った値
//返値 none
//-----------------------------------
void setRandomTable(std::vector<int>* randNumber, int rand){

	for (int i = 0; i < randNumber->size(); ++i){
		if (randNumber->at(i) == rand){
			return;
		}
	}
	randNumber->push_back(rand);
}
//--------------------------------------------------------
// 処理	コンストラクタ
// 引数	argMessage 受け取ったエラーメッセージ
// 返値	none
//--------------------------------------------------------
void logErrorCout(const exception::Exception& ex){

	std::cout << ex.getFileName() << "ファイルの" << std::endl;
	std::cout << ex.getFunction() << "関数の" << std::endl;
	std::cout << ex.getLineNumber() << "行目で" << std::endl;
	std::cout << ex.getMessage() << "というエラーが発生しています。確認してください" << std::endl;
}
//-----------------------------------
//処理 エラー情報出力
//引数 ex エラー内容
//返値 none
//-----------------------------------
void logErrorOutput(const exception::Exception& ex){

	std::string fileName = "Log.txt";//にエラーデータ追加try catchでの予期しないエラーはこちらに書き込み

	std::ofstream outputFile(fileName, std::ios_base::ate);

	outputFile << ex.getFileName() << "ファイルの" << std::endl;
	outputFile << ex.getFunction() << "関数の" << std::endl;
	outputFile << ex.getLineNumber() << "行目で" << std::endl;
	outputFile << ex.getMessage() << "というエラーが発生しています。" << std::endl << "確認してください" << std::endl;
	outputFile.close();
}
//-----------------------------------
//処理 MAPCHIPの読み込み
//引数 file
//　　 format
//返値 std::vector<std::string>
//-----------------------------------
std::vector<std::string> readFileData(const std::string& file, const std::string& format){

	std::string fileName = concatenate(file, format);

	//ファイル読み込み
	std::ifstream inputFile(fileName, std::ios_base::in);

	if (inputFile.fail()){
		THROW_EXCEPTION(exception::Exception, "ファイルが開けません");
	}

	std::vector<std::string> data;
	std::string str;

	while (getline(inputFile, str, '\n')){
		data.push_back(str);
		str.clear();
	}

	inputFile.close();

	return data;
}

//-----------------------------------
//処理 propertyNameを参考にdataの取り出し
//引数 data 探し元
//引数 propertyName 探す名前
//返値 探した名前に対応したデータ
//-----------------------------------
int parseProperty(const std::vector<std::string>& data, const char* propertyName){

	for (auto t : data){
		const std::string input = t;
		if (input.find(propertyName) != std::string::npos){
			const std::string pattern = "=";
			std::regex re(pattern);
			std::smatch match;
			int pos;

			if (std::regex_search(input, match, re)){
				pos = match.position();
				return std::stoi(input.substr(pos + 1, input.size()));
			}
		}
	}
	ASSERT(0, propertyName, STRING(propertyName), "が設定されませんでした");

	return 0;
}


//-----------------------------------
//処理 オレオレAssert(名づけ親:noob)
//引数 expression 表出
//　　 data errorデータ
//　　 dataName 名前
//　　 message errorデータ
//　　 argFile エラーが起きたファイル
//　　 argFunction エラーが起きた関数
//　　 argLine エラーが起きた行
//返値 none
//-----------------------------------
//template<typename type>
//void mockAssert(const int expression, const type data, const std::string& dataName, const std::string& message, const std::string& argFile, const std::string& argFunction, const int argLine){
//
//	if (expression == 0){
//		char strBuffer[1024];
//		if (sizeof(data) == sizeof(char)){
//			sprintf_s(strBuffer, "errorn情報:%s\n mesage:%s\n error数値:%c\n Assertion failed:%d\n file:%s\n function:%s\n line:%d\n",
//				dataName.c_str(), message.c_str(), data, expression, argFile.c_str(), argFunction.c_str(), argLine);
//		}
//		else if (sizeof(data) == sizeof(int)){
//			sprintf_s(strBuffer, "errorn情報:%s\n mesage:%s\n error数値:%d\n Assertion failed:%d\n file:%s\n function:%s\n line:%d\n",
//				dataName.c_str(), message.c_str(), data, expression, argFile.c_str(), argFunction.c_str(), argLine);
//		}
//		MessageBoxA(NULL, strBuffer, "メッセージ", MB_OK);
//	}
//}
////-----------------------------------
////処理 ファイルの改行コード毎一列毎にデータをわけて返す
////引数 file エラー内容
////引数 format .txt
////返値 vector<string>
////-----------------------------------