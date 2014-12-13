#include "Common.h"
#include <random>
#include <fstream>
#include <iostream>
#include <regex>
#include <assert.h>
#include <vector>
#include <atlstr.h>

//-----------------------------------
//���� �����A��
//���� fileName 
//�@�@ format		
//�Ԓl string �A����̕�����
//-----------------------------------
const std::string concatenate(const std::string& fileName, const std::string& format){

	std::string str = fileName + format;

	return str;
}
//-----------------------------------
//���� �����_���擾
//���� min �ŏ�
//�@�@ max �ő�
//�Ԓl int �����_���擾
//-----------------------------------
int getRandom(int min, int max){
	std::mt19937 rng{ std::random_device()() };
	std::uniform_int_distribution<int> dist(min, max);
	return dist(rng);
}
//-----------------------------------
//���� �����_���e�[�u���̃e�[�u�����ő�ɂȂ�܂Ŏ擾
//���� randMin �擾�l�̍ŏ�
//�@�@ randMax �擾�l�̍ő�
//�@�@ tableNum �e�[�u���̐�
//�Ԓl vector<int> �����_���e�[�u���擾
//-----------------------------------
std::vector<int> getRandomTable(int randMin, int randMax){
	int tableNum = (randMax + 1) - randMin;
	std::vector<int> randNumber;
	//��r�p��0�Ԗڂɒl�ǉ�
	randNumber.push_back(getRandom(randMin, randMax));

	while (randNumber.size() != tableNum){
		int rand = getRandom(randMin, randMax);
		setRandomTable(&randNumber, rand);
	}
	return randNumber;
}
//-----------------------------------
//���� �����_���e�[�u���ɒǉ�
//���� randNumber vector<int>*�ŏ�
//�@�@ rand �����_���Ŏ�����l
//�Ԓl none
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
// ����	�R���X�g���N�^
// ����	argMessage �󂯎�����G���[���b�Z�[�W
// �Ԓl	none
//--------------------------------------------------------
void logErrorCout(const exception::Exception& ex){

	std::cout << ex.getFileName() << "�t�@�C����" << std::endl;
	std::cout << ex.getFunction() << "�֐���" << std::endl;
	std::cout << ex.getLineNumber() << "�s�ڂ�" << std::endl;
	std::cout << ex.getMessage() << "�Ƃ����G���[���������Ă��܂��B�m�F���Ă�������" << std::endl;
}
//-----------------------------------
//���� �G���[���o��
//���� ex �G���[���e
//�Ԓl none
//-----------------------------------
void logErrorOutput(const exception::Exception& ex){

	std::string fileName = "Log.txt";//�ɃG���[�f�[�^�ǉ�try catch�ł̗\�����Ȃ��G���[�͂�����ɏ�������

	std::ofstream outputFile(fileName, std::ios_base::ate);

	outputFile << ex.getFileName() << "�t�@�C����" << std::endl;
	outputFile << ex.getFunction() << "�֐���" << std::endl;
	outputFile << ex.getLineNumber() << "�s�ڂ�" << std::endl;
	outputFile << ex.getMessage() << "�Ƃ����G���[���������Ă��܂��B" << std::endl << "�m�F���Ă�������" << std::endl;
	outputFile.close();
}
//-----------------------------------
//���� MAPCHIP�̓ǂݍ���
//���� file
//�@�@ format
//�Ԓl std::vector<std::string>
//-----------------------------------
std::vector<std::string> readFileData(const std::string& file, const std::string& format){

	std::string fileName = concatenate(file, format);

	//�t�@�C���ǂݍ���
	std::ifstream inputFile(fileName, std::ios_base::in);

	if (inputFile.fail()){
		THROW_EXCEPTION(exception::Exception, "�t�@�C�����J���܂���");
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
//���� propertyName���Q�l��data�̎��o��
//���� data �T����
//���� propertyName �T�����O
//�Ԓl �T�������O�ɑΉ������f�[�^
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
	ASSERT(0, propertyName, STRING(propertyName), "���ݒ肳��܂���ł���");

	return 0;
}


//-----------------------------------
//���� �I���I��Assert(���Â��e:noob)
//���� expression �\�o
//�@�@ data error�f�[�^
//�@�@ dataName ���O
//�@�@ message error�f�[�^
//�@�@ argFile �G���[���N�����t�@�C��
//�@�@ argFunction �G���[���N�����֐�
//�@�@ argLine �G���[���N�����s
//�Ԓl none
//-----------------------------------
//template<typename type>
//void mockAssert(const int expression, const type data, const std::string& dataName, const std::string& message, const std::string& argFile, const std::string& argFunction, const int argLine){
//
//	if (expression == 0){
//		char strBuffer[1024];
//		if (sizeof(data) == sizeof(char)){
//			sprintf_s(strBuffer, "errorn���:%s\n mesage:%s\n error���l:%c\n Assertion failed:%d\n file:%s\n function:%s\n line:%d\n",
//				dataName.c_str(), message.c_str(), data, expression, argFile.c_str(), argFunction.c_str(), argLine);
//		}
//		else if (sizeof(data) == sizeof(int)){
//			sprintf_s(strBuffer, "errorn���:%s\n mesage:%s\n error���l:%d\n Assertion failed:%d\n file:%s\n function:%s\n line:%d\n",
//				dataName.c_str(), message.c_str(), data, expression, argFile.c_str(), argFunction.c_str(), argLine);
//		}
//		MessageBoxA(NULL, strBuffer, "���b�Z�[�W", MB_OK);
//	}
//}
////-----------------------------------
////���� �t�@�C���̉��s�R�[�h����񖈂Ƀf�[�^���킯�ĕԂ�
////���� file �G���[���e
////���� format .txt
////�Ԓl vector<string>
////-----------------------------------