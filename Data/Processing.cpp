#include <iostream>
#include <string>

#include "Common.h"
#include "Random.h"

#include "Processing.h"
#include "Character.h"
#include "KeyInput.h"
//-----------------------------------
//���� �R���X�g���N�^
//���� 
//�Ԓl none 
//-----------------------------------
Processing::Processing(){
	mRandom = new Random();
	mCharacter = new Character();
	mKeyInput = new KeyInput();
	mState = GAME_INIT;
}
//-----------------------------------
//���� �f�X�g���N�^
//���� 
//�Ԓl none 
//-----------------------------------
Processing::~Processing(){
	delete mRandom;
	delete mCharacter;
	delete mKeyInput;
}
//-----------------------------------
//���� �S�f�[�^���܂Ƃ߂ĉ^�p
//���� 
//�Ԓl none 
//-----------------------------------
void Processing::doMainLoop(){

	mKeyInput->getKey();	//�L�[�擾

	switch (mState){
	case GAME_INIT:
			makeRandomMap();
			firstSetCharactorPos();
			mState = GAME_DRAW;
			break;
	case GAME_DRAW:
			system("cls");//�`��N���A
			draw(10);
			mCharacter->draw();
			mState = GAME_MAIN;
			break;
	case GAME_MAIN:
		bool getMoveFlag = keyPushAction();
			if (getMoveFlag){
				mState = GAME_DRAW;
			}
			break;
	}
}

void Processing::makeRandomMap(){
	static bool readMapChipFlag = true;
	//int oneSize = 50;
	//
	if (readMapChipFlag == true){
		mMap.push_back(Map("map", 80, 80, '#'));

		mMap.push_back(Map("Square7x7", ".txt"));
		readMapChipFlag = false;
	}
	//init
	mapClear(0, '#');

	setMapChipDataCheck(15, 16, 2);

	setRandomPassagePosition(2, 16);

	setConsolidatedPassage();

	setStairs();

	changePassageToSpace();
}
//-----------------------------------
//���� �S��MAP�Ƀf�[�^��ǉ����Ă��� range�͔͈͂��i��
//���� roomNumMax 	int	�����̐�
//�@�@ argSide		int �S��MAP�̃T�C�Y��argSide�����킯��
//�@�@ range			int  range ~ width-range �͈�
//�Ԓl none 
//-----------------------------------
void Processing::setMapChipDataCheck(int roomNumMax, int argSide, int range){
	
	int splitX = mMap.at(0).getWidth() / argSide;
	int splitY = mMap.at(0).getHeight() / argSide;

	int roomCheckNum = 0;

	std::vector<int> randTable;//roomMax���͓���p
	mRandom->prepareLump(0, 1, &randTable, 1, roomNumMax, splitX * splitY);
	int randTableIndex = 0;
	for (int y = 0; y < splitY; ++y){

		std::vector<int> randTableSame;//roomSame���͓���p
		int randTableSameindex = 0;
		mRandom->sameLump(1, mMap.size() - 1, &randTableSame, splitX);
		for (int x = 0; x < splitX; ++x){
			if (roomCheckNum < roomNumMax){
				if (randTable[randTableIndex++] == 1){
					
					int index = randTableSame[randTableSameindex++];
					int firstX = getStartPositionX(range, index, mMap, argSide, x);
					int firstY = getStartPositionY(range, index, mMap, argSide, y);
					setMapChip(firstX,firstY,index,mMap);
					++roomCheckNum;
				}
			}
		}
		randTableSame.clear();
	}
	randTable.clear();
}
//-----------------------------------
//���� �S��MAP�Ƀf�[�^��ǉ����Ă��� range�͔͈͂��i��
//���� range 	int	�͈�
//�@�@ index		int �ǂ̃}�b�v�`�b�v�̗v�f
//�@�@ mapChip	const std::vector<Map>& �}�b�v�`�b�v�̃f�[�^
//�@�@ argSide	int  �T�C�Y
//�@�@ nowSplit	int  ���݂�split�v�f�ʒu�@argSide * x 
//�Ԓl �J�n�ʒu + nowSplit * argSide�@range  + (argSide * nowSplit)
//-----------------------------------
int Processing::getStartPositionX(int range, int index, const std::vector<Map>& mapChip, int argSide,int nowSplit){
	return (getRandom(range, argSide - range - (mapChip.at(index).getWidth() - 1)) + (argSide * nowSplit));
}
int Processing::getStartPositionY(int range, int index, const std::vector<Map>& mapChip, int argSide, int nowSplit){
	return (getRandom(range, argSide - range - (mapChip.at(index).getHeight() - 1)) + (argSide * nowSplit));
}
//-----------------------------------
//���� �S��MAP�Ƀ}�b�v�`�b�v��ǉ��@
//���� firstX 	int	�J�n�ʒuX
//�@�@ firstY	int �J�n�ʒuY
//�@�@ index	 int �v�f
//�@�@ map	std::vector<Map> �}�b�v�`�b�v�̎�ނ�I��
//�Ԓl none
//-----------------------------------
void Processing::setMapChip(int firstX, int firstY, int index, const std::vector<Map> map){
	for (int y = 0; y < map.at(index).getHeight(); ++y){
		for (int x = 0; x < map.at(index).getWidth(); ++x){
			if (mMap.at(0).getData()(x + firstX, y + firstY) == '#'){
				mMap.at(0).getData()(x + firstX, y + firstY) = map.at(index).getData()(x, y);
			}
		}
	}
}
//-----------------------------------
//���� �����_���ŋ󔒂̈ʒu��t�Ƃ��Ď擾���Ă��̃|�W�V������consolidatedList�ɒǉ�
//���� range�@int	�����͈�
//�@�@ argSide	int �����T�C�Y
//�Ԓl none
//-----------------------------------
void Processing::setRandomPassagePosition(int range,int argSide){

	int splitX = mMap.at(0).getWidth() / argSide;
	int splitY = mMap.at(0).getHeight() / argSide;

	for (int y = 0; y < splitY; ++y){
		for (int x = 0; x < splitX; ++x){

			int firstX = argSide * x;
			int firstY = argSide * y;

			Position randomSpacePos = getRandomSpacePosition(range,argSide, firstX, firstY);

			if (randomSpacePos.x != 0 && randomSpacePos.y != 0){
				mMap.at(0).getData()(randomSpacePos.x, randomSpacePos.y) = 't';
				consolidatedList.push_back(randomSpacePos);
			}
		}
	}
}
//-----------------------------------
//���� �����_����x,y�Ŏ擾
//���� argSide�@
//�@�@ firstX	
//�@�@ firstY �@
//�Ԓl at(index).List(x,y)
//-----------------------------------
Processing::Position Processing::getRandomSpacePosition(int range, int argSide, int firstX, int firstY){

	std::vector<Position> spacePosition;

	for (int y = range; y < argSide-range; ++y){
		for (int x = range; x < argSide - range; ++x){
			if (mMap.at(0).getData()(x + firstX, y + firstY) == ' '){
				spacePosition.push_back(Position(x + firstX, y + firstY));
			}
		}
	}
	if(spacePosition.size() == 0){
		spacePosition.push_back(Position(0,0));
		return spacePosition.at(0);
	}
	int index = getRandom(0, spacePosition.size() - 1);

	return spacePosition.at(index);
}
//-----------------------------------
//���� �ʘH���m�̘A��
//���� �@
//�Ԓl none
//-----------------------------------
void Processing::setConsolidatedPassage(){

	int width = mMap.at(0).getWidth();

	int splitX = mMap.at(0).getWidth() / 2;
	int splitY = mMap.at(0).getHeight() / 2;

	std::vector<struct Position> lWaySapcePos;
	std::vector<struct Data> lDistance;

	std::vector<std::string> strList = { "leftup", "rightup", "leftdown", "rightdown", "up", "down", "all" };

	for (auto t : strList){
		bool getWay = setWayConsolidatedList(t, &lWaySapcePos);
		
		if (getWay == true){
			for (int i = 0; i < static_cast<int>(lWaySapcePos.size()); ++i){

				bool getDis = setDistanceConsolidatedList(i, lWaySapcePos, &lDistance);
				
				int index = 0;
				if (getDis == true){
					for (int j = 0; j < static_cast<int>(lDistance.size()); ++j){
						index = getNeaIndexrDistancePos(index, lDistance);	
					}
					if (index != -1){
						consolidatedPassage(index, lDistance);
					}
				}
				lDistance.clear();
			}
		}
		lWaySapcePos.clear();
	}
	strList.clear();

	std::vector<struct Position> lComparisonSourcePos;
	std::vector<struct Position> lComparisonDestinationPos;
	strList = { "up", "down", "all" };
	for (auto t : strList){
		bool getWay = setWayConsolidatedList(t, &lComparisonSourcePos, &lComparisonDestinationPos);
		if (getWay == true){
			bool getDis = setDistanceConsolidatedList(lComparisonSourcePos, lComparisonDestinationPos, &lDistance);
			int index = 0;
			if (getDis == true){
				index = getNeaIndexrDistancePos(lDistance);
			}
			if (index != -1){
				consolidatedPassage(index, lDistance);
			}
			lDistance.clear();
		}
		lComparisonSourcePos.clear();
		lComparisonDestinationPos.clear();
	}
}
//-----------------------------------
//���� way�����ɂ���f�[�^������wayPos�Ɋi�[
//���� way const char*	�ǂ������̃f�[�^��
//�@�@ wayPos std::vector<struct Position>* �i�[�p
//�Ԓl none
//-----------------------------------
bool Processing::setWayConsolidatedList(const std::string& way, std::vector<struct Position>* wayPos){

	int splitX = mMap.at(0).getWidth() / 2;
	int splitY = mMap.at(0).getHeight() / 2;

	if (way == "leftup"){
		for (int index = 0; index < static_cast<int>(consolidatedList.size()); ++index){
			if (consolidatedList.at(index).x <= splitX &&
				consolidatedList.at(index).y <= splitY){

				wayPos->push_back(Position(consolidatedList.at(index).x, consolidatedList.at(index).y));
			}
		}
	}
	else if (way == "rightup"){
		for (int index = 0; index < static_cast<int>(consolidatedList.size()); ++index){
			if (consolidatedList.at(index).x > splitX &&
				consolidatedList.at(index).y <= splitY){

				wayPos->push_back(Position(consolidatedList.at(index).x, consolidatedList.at(index).y));
			}
		}
	}
	else if (way == "leftdown"){
		for (int index = 0; index < static_cast<int>(consolidatedList.size()); ++index){
			if (consolidatedList.at(index).x <= splitX &&
				consolidatedList.at(index).y > splitY){

				wayPos->push_back(Position(consolidatedList.at(index).x, consolidatedList.at(index).y));
			}
		}
	}
	else if (way == "rightdown"){
		for (int index = 0; index < static_cast<int>(consolidatedList.size()); ++index){
			if (consolidatedList.at(index).x > splitX &&
				consolidatedList.at(index).y > splitY){

				wayPos->push_back(Position(consolidatedList.at(index).x, consolidatedList.at(index).y));
			}
		}
	}	
	return wayPos->size();
}

bool Processing::setWayConsolidatedList(const std::string& way, std::vector<struct Position>* lComparisonSourcePos, std::vector<struct Position>* lComparisonDestinationPos){
	int splitX = mMap.at(0).getWidth() / 2;
	int splitY = mMap.at(0).getHeight() / 2;
	if (way == "up"){
		for (int index = 0; index < static_cast<int>(consolidatedList.size()); ++index){
			if (consolidatedList.at(index).x <= splitX &&
				consolidatedList.at(index).y <= splitY){

				lComparisonSourcePos->push_back(Position(consolidatedList.at(index).x, consolidatedList.at(index).y));
			}
		}
		for (int index = 0; index < static_cast<int>(consolidatedList.size()); ++index){
			if (consolidatedList.at(index).x > splitX &&
				consolidatedList.at(index).y <= splitY){

				lComparisonDestinationPos->push_back(Position(consolidatedList.at(index).x, consolidatedList.at(index).y));
			}
		}
	}
	else if (way == "down"){
		for (int index = 0; index < static_cast<int>(consolidatedList.size()); ++index){
			if (consolidatedList.at(index).x <= splitX &&
				consolidatedList.at(index).y > splitY){

				lComparisonSourcePos->push_back(Position(consolidatedList.at(index).x, consolidatedList.at(index).y));
			}
		}
		for (int index = 0; index < static_cast<int>(consolidatedList.size()); ++index){
			if (consolidatedList.at(index).x > splitX &&
				consolidatedList.at(index).y > splitY){

				lComparisonDestinationPos->push_back(Position(consolidatedList.at(index).x, consolidatedList.at(index).y));
			}
		}
	}
	else if (way == "all"){
		for (int index = 0; index < static_cast<int>(consolidatedList.size()); ++index){
			if (consolidatedList.at(index).y < splitY){

				lComparisonSourcePos->push_back(Position(consolidatedList.at(index).x, consolidatedList.at(index).y));
			}
		}
		for (int index = 0; index < static_cast<int>(consolidatedList.size()); ++index){
			if (consolidatedList.at(index).y > splitY){

				lComparisonDestinationPos->push_back(Position(consolidatedList.at(index).x, consolidatedList.at(index).y));
			}
		}
	}
	if (lComparisonDestinationPos->size() != 0 && lComparisonSourcePos->size() != 0){
		return true;
	}
	return false;
}
//-----------------------------------
//���� ��r����v�f�Ƃ��ׂĂ̗v�f���r���Ċi�[
//���� comparisonIndex int	��r�v�f
//�@�@ wayPos std::vector<struct Position>& �`�F�b�N�p
//�@�@ disPos std::vector<struct Data>* �i�[�p
//�Ԓl none
//-----------------------------------
bool Processing::setDistanceConsolidatedList(int comparisonIndex,const std::vector<struct Position>& wayPos, std::vector<struct Data>* disPos){
	for (int index = comparisonIndex + 1; index < static_cast<int>(wayPos.size()); ++index){
		int oldPosX = wayPos.at(comparisonIndex).x;
		int oldPosY = wayPos.at(comparisonIndex).y;

		int posX = wayPos.at(index).x;
		int posY = wayPos.at(index).y;

		disPos->push_back(Data(oldPosX,posX,oldPosY,posY));
	}
	return disPos->size();
}
bool Processing::setDistanceConsolidatedList(const std::vector<struct Position>& lComparisonSourcePos, const std::vector<struct Position>& lComparisonDestinationPos, std::vector<struct Data>* disPos){

	for (int i = 0; i < static_cast<int>(lComparisonSourcePos.size()); ++i){
		for (int j = 0; j < static_cast<int>(lComparisonDestinationPos.size()); ++j){
			int oldPosX = lComparisonSourcePos.at(i).x;
			int oldPosY = lComparisonSourcePos.at(i).y;

			int posX = lComparisonDestinationPos.at(j).x;
			int posY = lComparisonDestinationPos.at(j).y;

			disPos->push_back(Data(oldPosX, posX, oldPosY, posY));
		}
	}
	return disPos->size();
}
//-----------------------------------
//���� ��r�p�̗v�f�𒲂ׂĈ�ԍŏ��̋�����index��Ԃ�
//���� comparisonIndex int	��r�v�f
//�@�@ disPos const std::vector<struct Position>& �`�F�b�N�p
//�Ԓl none
//-----------------------------------
int Processing::getNeaIndexrDistancePos(int comparisonIndex, const std::vector<struct Data>& disPos){
	int distance = 100;
	for (int index = comparisonIndex; index < static_cast<int>(disPos.size()); ++index){
		if (distance >= disPos.at(index).distance){
			distance = disPos.at(index).distance;
		}
	}
	//return index
	for (int index = 0; index < static_cast<int>(disPos.size()); ++index){
		if (distance == disPos.at(index).distance){
			return index;
		}
	}
	return -1;
}
int Processing::getNeaIndexrDistancePos(const std::vector<struct Data>& disPos){
	int distance = 100;
	for (int index = 0; index < static_cast<int>(disPos.size()); ++index){
		if (distance >= disPos.at(index).distance){
			distance = disPos.at(index).distance;
		}
	}
	//return index
	for (int index = 0; index < static_cast<int>(disPos.size()); ++index){
		if (distance == disPos.at(index).distance){
			return index;
		}
	}
	return -1;
}
//-----------------------------------
//���� ��r�p�̗v�f�𒲂ׂĈ�ԍŏ��̋�����index��Ԃ�
//���� comparisonIndex int	��r�v�f
//�@�@ disPos const std::vector<struct Position>& �`�F�b�N�p
//�Ԓl none
//-----------------------------------
void Processing::consolidatedPassage(int index, const std::vector<struct Data>& disPos){

	if (disPos.size() == 0) return;

	int oldPosX = disPos.at(index).firstX;
	int oldPosY = disPos.at(index).firstY;
	int MidpointX = disPos.at(index).MidpointX;
	int MidpointY = disPos.at(index).MidpointY;
	int posX = disPos.at(index).endX;
	int posY = disPos.at(index).endY;

	if (oldPosX <= MidpointX){
		setConsolidated(oldPosX, MidpointX, 0, oldPosY);
		if (MidpointX <= posX){
			setConsolidated(MidpointX, posX, 0, posY);
			if (oldPosY <= MidpointY){
				setConsolidated(oldPosY, MidpointY, MidpointX, 0);
				if (MidpointY <= posY){
					setConsolidated(MidpointY, posY, MidpointX, 0);
				}
				else{
					setConsolidated(posY, MidpointY, MidpointX, 0);
				}
			}
			else{
				setConsolidated(MidpointY, oldPosY, MidpointX, 0);
				if (MidpointY <= posY){
					setConsolidated(MidpointY, posY, MidpointX, 0);
				}
				else{
					setConsolidated(posY, MidpointY, MidpointX, 0);
				}
			}
		}
		else{
			setConsolidated(posX, MidpointX, 0, posY);
			if (oldPosY <= MidpointY){
				setConsolidated(oldPosY, MidpointY, MidpointX, 0);
				if (MidpointY <= posY){
					setConsolidated(MidpointY, posY, MidpointX, 0);
				}
				else{
					setConsolidated(posY, MidpointY, MidpointX, 0);
				}
			}
			else{
				setConsolidated(MidpointY, oldPosY, MidpointX, 0);
				if (MidpointY <= posY){
					setConsolidated(MidpointY, posY, MidpointX, 0);
				}
				else{
					setConsolidated(posY, MidpointY, MidpointX, 0);
				}
			}
		}
	}
	else{
		setConsolidated(MidpointX, oldPosX, 0, oldPosY);
		if (MidpointX <= posX){
			setConsolidated(MidpointX, posX, 0, posY);
			if (oldPosY <= MidpointY){
				setConsolidated(oldPosY, MidpointY, MidpointX, 0);
				if (MidpointY <= posY){
					setConsolidated(MidpointY, posY, MidpointX, 0);
				}
				else{
					setConsolidated(posY, MidpointY, MidpointX, 0);
				}
			}
			else{
				setConsolidated(MidpointY, oldPosY, MidpointX, 0);
				if (MidpointY <= posY){
					setConsolidated(MidpointY, posY, MidpointX, 0);
				}
				else{
					setConsolidated(posY, MidpointY, MidpointX, 0);
				}
			}
		}
		else{
			setConsolidated(posX, MidpointX, 0, posY);
			if (oldPosY <= MidpointY){
				setConsolidated(oldPosY, MidpointY, MidpointX, 0);
				if (MidpointY <= posY){
					setConsolidated(MidpointY, posY, MidpointX, 0);
				}
				else{
					setConsolidated(posY, MidpointY, MidpointX, 0);
				}
			}
			else{
				setConsolidated(MidpointY, oldPosY, MidpointX, 0);
				if (MidpointY <= posY){
					setConsolidated(MidpointY, posY, MidpointX, 0);
				}
				else{
					setConsolidated(posY, MidpointY, MidpointX, 0);
				}
			}
		}
	}
}

void Processing::setConsolidated(int firstPos, int endPos, int posX, int posY){
	
	if (posX){
		for (int y = firstPos; y <= endPos; ++y){
			mMap.at(0).getData()(posX, y) = 't';
		}
	}
	else if (posY){
		for (int x = firstPos; x <= endPos; ++x){
			mMap.at(0).getData()(x, posY) = 't';
		}
	}
}
//-----------------------------------
//���� map�S�̂̉������ɉ����K�i���쐬 �K�i�̈ʒu��stairs�ɒǉ�
//���� none
//�Ԓl none
//-----------------------------------
void Processing::setStairs(){
	int stairsPosX = 0;
	int stairsPosY = 0;
	do{
		stairsPosX = mRandom->getRandom(0, mMap.at(0).getWidth() - 1);
		stairsPosY = mRandom->getRandom(0, mMap.at(0).getHeight() - 1);
	} while (mMap.at(0).getData()(stairsPosX, stairsPosY) != ' ');

	mMap.at(0).getData()(stairsPosX, stairsPosY) = 's';

	stairs.x = stairsPosX;
	stairs.y = stairsPosY;
}
//-----------------------------------
//���� map�S�̂̒ʘH�������X�y�[�X�ɕϊ�
//���� none
//�Ԓl none
//-----------------------------------
void Processing::changePassageToSpace(){
	int width = mMap.at(0).getWidth();
	int height = mMap.at(0).getHeight();

	for (int y = 0; y < height; ++y){
		for (int x = 0; x < width; ++x){

			if (mMap.at(0).getData()(x, y) == 't'){
				mMap.at(0).getData()(x, y) = ' ';
			}
		}
	}
}
//-----------------------------------
//���� �L�����ʒu���󔒈ʒu�ɃZ�b�g c
//���� none
//�Ԓl none
//-----------------------------------
void Processing::firstSetCharactorPos(){
	int charactorPosX =0;
	int charactorPosY =0;
	do{
		charactorPosX = mRandom->getRandom(0, mMap.at(0).getWidth()-1);
		charactorPosY = mRandom->getRandom(0, mMap.at(0).getHeight()-1);
	} while (mMap.at(0).getData()(charactorPosX, charactorPosY) != ' ');
	
	mCharacter->setX(charactorPosX);
	mCharacter->setY(charactorPosY);

	mMap.at(0).getData()(charactorPosX, charactorPosY) = 'c';
}
//-----------------------------------
//���� �S��MAP�̏o��
//���� ������͈�
//�Ԓl none
//-----------------------------------
void Processing::draw(int viewRange){

	int width = mMap.at(0).getWidth();
	int height = mMap.at(0).getHeight();

	Position charctorPos = getCharctorPos();
	int minViewRangeX, maxViewRangeX;
	int minViewRangeY, maxViewRangeY;
	setDrawRangeMinMax(&minViewRangeX, &maxViewRangeX, charctorPos.x, viewRange, width);
	setDrawRangeMinMax(&minViewRangeY, &maxViewRangeY, charctorPos.y, viewRange, height);

	for (int y = minViewRangeY; y < maxViewRangeY; ++y){
		for (int x = minViewRangeX; x < maxViewRangeX; ++x){

			switch (mMap.at(0).getData()(x, y)){
			case '#':
				std::cout << "��";
				break;
			case 'c':
				std::cout << "��";
				break;
			case 't':
				std::cout << "��";
				break;
			case 's':
				std::cout << "�K";
				break;
			default:
				std::cout << "�@";
			}
		}
		std::cout << std::endl;
	}
}
//-----------------------------------
//���� min max�͈̔͂��Z�b�g
//���� minNum	int*	
//�@�@ maxNum	int*
//�@�@ charctorPos	int	�L�����ʒu�̃|�W�V����
//�@�@ range		const int ������͈�
//�@�@ maxLength		const int ������͈͂̍ő�ʒu
//�Ԓl none
//-----------------------------------
void Processing::setDrawRangeMinMax(int* minNum, int* maxNum, int charctorPos, const int range, const int maxLength){
	
	if (charctorPos - range <= 0){
		*minNum = 0;
		*maxNum = range * 2;
	}
	else{
		*minNum = charctorPos - range;
		if (charctorPos + range >= maxLength){
			*maxNum = maxLength;
			*minNum = maxLength - (range * 2);
		}
		else{
			*maxNum = charctorPos + range;
		}
	}
	ASSERT(0 <= *minNum && *minNum <= maxLength, *minNum, STRING(minNum), "minNum�̐��l���͈͊O�ɂȂ��Ă��܂�");
	ASSERT(0 <= *maxNum && *maxNum <= maxLength, *maxNum, STRING(maxNum), "maxNum�̐��l���͈͊O�ɂȂ��Ă��܂�");
}
//-----------------------------------
//���� �L�����N�^�[�̃|�W�V�����𓾂�
//���� 
//�Ԓl Position
//-----------------------------------
Processing::Position Processing::getCharctorPos(){

	int width = mMap.at(0).getWidth();
	int height = mMap.at(0).getHeight();

	int charctorPosX = 0;
	int charctorPosY = 0;

	for (int y = 0; y < height; ++y){
		for (int x = 0; x < width; ++x){

			if (mMap.at(0).getData()(x, y) == 'c'){
				int charctorPosX = x; 	
				int charctorPosY = y;
				Position charctorPos(charctorPosX, charctorPosY);
				return charctorPos;
			}
		}
	}
	ASSERT(0, charctorPosX + charctorPosY, STRING(charctorPos), "�L�����N�^�[���}�b�v�ɑ��݂��܂���");
	return Position(0, 0);
}

bool Processing::charactorMove(Position charctorPos,int VX,int VY){

	if (mMap.at(0).getData()(charctorPos.x + VX, charctorPos.y + VY) == ' '){
		mMap.at(0).getData()(charctorPos.x, charctorPos.y) = ' ';
		mMap.at(0).getData()(charctorPos.x + VX, charctorPos.y + VY) = 'c';
		mCharacter->Move(VX, VY);
		return true;
	}
	else if (mMap.at(0).getData()(charctorPos.x + VX, charctorPos.y + VY) == 's'){
		mState = GAME_INIT;
	}
	return false;
}
bool Processing::keyPushAction(){
	Position charctorPos = getCharctorPos();

	if (mKeyInput->getKeyIndex(KEY_A) == true || mKeyInput->getKeyIndex(KEY_LEFT) == true){
		
		return charactorMove(charctorPos, -1, 0);
	}
	else if (mKeyInput->getKeyIndex(KEY_D) == true || mKeyInput->getKeyIndex(KEY_RIGHT) == true){
		
		return charactorMove(charctorPos, 1, 0);
	}
	else if (mKeyInput->getKeyIndex(KEY_W) == true || mKeyInput->getKeyIndex(KEY_UP) == true){
		
		return charactorMove(charctorPos, 0, -1);
	}
	else if (mKeyInput->getKeyIndex(KEY_S) == true || mKeyInput->getKeyIndex(KEY_DOWN) == true){
		
		return charactorMove(charctorPos, 0, 1);
	}
	return false;
};

void Processing::mapClear(int index, const char charctor){
	int width = mMap.at(0).getWidth();
	int height = mMap.at(0).getHeight();

	for (int y = 0; y < height; ++y){
		for (int x = 0; x < width; ++x){
			mMap.at(index).getData()(x, y) = charctor;
		}
	}
}