#include "Random.h"
#include "Common.h"
//-----------------------------------
//���� �R���X�g���N�^
//���� min �ŏ�
//�@�@ max �ő�
//�Ԓl none
//-----------------------------------
Random::Random(int min, int max) :parameter(min, max){
	
};
//-----------------------------------
//���� �f�X�g���N�^

//�Ԓl none
//-----------------------------------
Random::~Random(){

}
//-----------------------------------
//���� �����_���擾
//���� min �ŏ�
//�@�@ max �ő�
//�Ԓl int �����_���擾
//-----------------------------------
const int Random::getRandom(int min, int max)const throw(){
	std::mt19937 rng{ std::random_device()() };
	std::uniform_int_distribution<int> dist(min, max);
	return dist(rng);
}

//-----------------------------------
//���� �ŏ��ő�̐ݒ�
//���� argMin int	�ŏ�
//�@�@ argMax int	�ő�
//�Ԓl none
//-----------------------------------
void Random::setParameterMinMax(int argMin, int argMax)throw(){
	this->parameter.min = argMin;
	this->parameter.max = argMax;
}
//-----------------------------------
//���� �����_���e�[�u���̏�����
//�Ԓl none
//-----------------------------------
void Random::clearRandomTable()throw(){
	randomTable.clear();
}
//-----------------------------------
//���� �����_���e�[�u���̃T�C�Y��Ԃ�
//�Ԓl �����_���e�[�u���̃T�C�Y
//-----------------------------------
int Random::getRandomTableSize()throw(){
	return randomTable.size();
}

//-----------------------------------
//���� �����_���e�[�u���ɒǉ����ꂽ�f�[�^�ƈ���rand���Ⴄ���m�F
//���� rand minmax�͈͂Ŏ���������_���l
//�Ԓl ��(true) ��(false) 
//-----------------------------------
bool Random::checkRandomTable(int rand)throw(){

	for (int i = 0; i < static_cast<int>(randomTable.size()); ++i){
		if (randomTable.at(i) == rand){
			return false;
		}
	}
	return true;
}
//-----------------------------------
//���� �����_���e�[�u���̃e�[�u�����ő�ɂȂ�܂Ŏ擾 �K���قȂ鐔�l���e�[�u���ɓ���
//���� tableNum int	�e�[�u���̐�
//�Ԓl none
//-----------------------------------
void Random::setRandomTableDifferentNumberPossibleIsEntered(int tableNum)throw(){

	int randMin = parameter.min;
	int randMax = parameter.max;
	int minmaxRange = (abs(randMax) + 1) - abs(randMin);
	ASSERT(minmaxRange >= tableNum, minmaxRange, STRING(minmaxRange), "�e�[�u���̐��ƈقȂ郉���_���f�[�^������e�[�u���̐�����v���Ă��܂���");

	clearRandomTable();
	//tableNum���f�t�H���g�����̏ꍇ�@
	if (tableNum == 0){
		tableNum = (abs(randMax) + 1) - abs(randMin);
	}

	////��r�p��0�Ԗڂɒl�ǉ�
	//randomTable.push_back(getRandom(randMin, randMax));

	while (randomTable.size() != tableNum){
		int rand = getRandom(randMin, randMax);
		if (checkRandomTable(rand)){
			randomTable.push_back(rand);
		};	//�قȂ������������Ă邩�m�F���ē����	
	}
}
//-----------------------------------
//���� �����_���e�[�u���̃e�[�u�����ő�ɂȂ�܂Ń����_���l���擾 (�������l�ł���)
//���� tableNum int	�e�[�u���̐�
//�Ԓl none
//-----------------------------------
void Random::setRandomTableSameNumberPossibleIsEntered(int tableNum)throw(){

	int randMin = parameter.min;
	int randMax = parameter.max;

	clearRandomTable();
	//tableNum���f�t�H���g�����̏ꍇ�@
	if (tableNum == 0){
		tableNum = (abs(randMax) + 1) - abs(randMin);
	}

	////��r�p��0�Ԗڂɒl�ǉ�
	//randomTable.push_back(getRandom(randMin, randMax));

	while (randomTable.size() != tableNum){
		int rand = getRandom(randMin, randMax);
		randomTable.push_back(rand);
	}
}
//-----------------------------------
//���� �����_���e�[�u���̃e�[�u�����R�s�[ 
//���� inputRandTable std::vector<int>*	�R�s�[�p
//�Ԓl none
//-----------------------------------
void Random::getRandomTable(std::vector<int>* inputRandTable)throw(){

	for (int index = 0; index < static_cast<int>(randomTable.size()); ++index){
		inputRandTable->push_back(randomTable[index]);
	}
}
//-----------------------------------
//���� �����l�����肤�郉���_���������܂Ƃ߂�
//���� setMin		int	�Ƃ肤��ŏ��l
//�@�@ setMax		int �Ƃ肤��ő�l
//�@�@ randTable		std::vector<int>*�@�R�s�[�p
//�@�@ tableNum		int �����_���e�[�u���̗v�f�̐��w��
//�Ԓl none
//-----------------------------------
void Random::sameLump(int setMin, int setMax, std::vector<int>* randTable, int tableNum){
	setParameterMinMax(setMin, setMax);
	setRandomTableSameNumberPossibleIsEntered(tableNum);
	getRandomTable(randTable);
}
//-----------------------------------
//���� �قȂ�l�����肤�郉���_���������܂Ƃ߂�
//���� setMin		int	�Ƃ肤��ŏ��l
//�@�@ setMax		int �Ƃ肤��ő�l
//�@�@ randTable		std::vector<int>*�@�R�s�[�p
//�@�@ tableNum		int �����_���e�[�u���̗v�f�̐��w��
//�Ԓl none
//-----------------------------------
void Random::diffLump(int setMin, int setMax, std::vector<int>* randTable, int tableNum){
	setParameterMinMax(setMin, setMax);
	setRandomTableDifferentNumberPossibleIsEntered(tableNum);
	getRandomTable(randTable);
}
//���鐔�l�������_����ŕK�����̌����͏o�������_��
//-----------------------------------
//���� value�̐��l��randInvalueNum�͊m���ɓ��郉���_���������܂Ƃ߂�
//���� setMin		int	�Ƃ肤��ŏ��l
//�@�@ setMax		int �Ƃ肤��ő�l
//�@�@ randTable		std::vector<int>*�@�R�s�[�p
//�@�@ value			int �m���ɓ��ꂽ���v�f
//�@�@ randInValueNum�@int �m���ɓ��ꂽ���v�f�̐�
//�@�@ tableNum		int �����_���e�[�u���̗v�f�̐��w��
//�Ԓl none
//-----------------------------------
void Random::prepareLump(int setMin, int setMax, std::vector<int>* randTable, int value, int randInValueNum, int tableNum){
	setParameterMinMax(setMin, setMax);
	setRandomTableValueSetRandInValueNum(value, randInValueNum, tableNum);
	getRandomTable(randTable);
}

//���鐔�l�������_����ŕK�����̌����͏o�������_��
//-----------------------------------
//���� value�̐��l��randInvalueNum�͊m���ɓ��郉���_���������܂Ƃ߂�
//���� value		int	�m���ɓ��ꂽ���v�f
//�@�@ randInValueNum	int �m���ɓ��ꂽ���v�f�̐�
//�@�@ tableNum�@int �����_���e�[�u���̗v�f�̐��w��
//�Ԓl none
//-----------------------------------
void Random::setRandomTableValueSetRandInValueNum(int value, int randInValueNum, int tableNum)throw(){

	ASSERT(tableNum >= randInValueNum, tableNum - randInValueNum, STRING(tableNum - randInValueNum), "�ǉ��������v�f�̐����e�[�u���̐������Ȃ��ł�");
	//min max�}�N�������邩��ASSERT�̈��������Ɏg����B
	int randMin = parameter.min;
	int randMax = parameter.max;
	ASSERT(randMin <= value &&  value <= randMax, value, STRING(value), "�ǉ��������v�f���ő�ŏ��T�C�Y�̒��ɓ����Ă��܂���");

	int valueNum = 0;
	clearRandomTable();
	//tableNum���f�t�H���g�����̏ꍇ�@
	if (tableNum == 0){
		tableNum = (abs(randMax) + 1) - abs(randMin);
	}

	////��r�p��0�Ԗڂɒl�ǉ�
	//randomTable.push_back(getRandom(randMin, randMax));
	//if (randomTable.at(0) == value){
	//	++valueNum;
	//}
	/*
	while
	�e�[�u���ƃT�C�Y�̐�����v����܂ł��A
	�m���ɓ����v�f�̎c��@< �c��ǉ��e�[�u���̐�
	(�m���ɓ����v�f��-�������Ă�m���ɓ����v�f�@< �e�[�u�� - �����_���e�[�u���̃T�C�Y)`
	�������Ă�v�f�����m���ɓ����v�f�����Ⴂ�Ȃ�
	min max�͈̔͂��畁�ʂɒl���擾���āA�f�[�^���i�[

	�������̏����𔲂����Ƃ��āA
	if
	�m���ɓ����v�f�̎c��@< �c��ǉ��e�[�u���̐��Ȃ�
	�c��S����ǉ��������v�f�Œǉ�
	else
	�m���ɓ����v�f��<�������Ă�m���ɓ����v�f���Ȃ�
	�܂�m���ɓ����v�f�͂������݂��Ȃ��̂�
	���Ƃ͊m���ɓ����v�f�ӊO�������_���ŗ����ꍇ�̂ݒǉ�

	�e�[�u���ƃT�C�Y�̐�����v����܂ł�
	���̈Ӗ��ʂ�ł����A�K���ǂ������ň���������̂ł���͂����H
	*/

	while (randomTable.size() != tableNum &&
		randInValueNum - valueNum < tableNum - static_cast<int>(randomTable.size()) &&//�m���ɓ��ꂽ���v�f��-�������Ă�m���ɓ��ꂽ���v�f��
		valueNum < randInValueNum){

		int rand = getRandom(randMin, randMax);
		if (rand == value){
			++valueNum;
		}
		randomTable.push_back(rand);
	}
	//value�Ɠ����l������
	if (valueNum < randInValueNum){
		while (valueNum != randInValueNum){
			randomTable.push_back(value);
			++valueNum;
		}
	}
	else{//value�Ɠ����l������Ȃ��悤�ɂ���
		while (randomTable.size() != tableNum){
			int rand = getRandom(randMin, randMax);
			if (rand != value){
				randomTable.push_back(rand);
			}
		}
	}
}