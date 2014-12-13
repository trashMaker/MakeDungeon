#pragma once
#include <vector>

#include "Map.h"

class Random;

class Processing{
private:
	std::vector<Map> mMap;
	std::vector<Map> mMiniChip;

	struct Position{
		int x;
		int y;
		Position(int x, int y){
			this->x = x;
			this->y = y;
		}
	};

	std::vector<struct Position> consolidatedList;	//space random potision

	Random* mRandom;

	struct Data{
		int firstX;
		int endX;
		int firstY;
		int endY;
		int MidpointX;
		int MidpointY;
		int distance;

		Data(int argFirstX, int argEndX, int argFirstY, int argEndY){
			firstX = argFirstX;
			endX = argEndX;
			firstY = argFirstY;
			endY = argEndY;
			MidpointX = (argFirstX + argEndX) / 2;
			MidpointY = (argFirstY + argEndY) / 2;
			distance = static_cast<int>(sqrt(pow((argEndX - argFirstX), 2) + pow((argEndY - argFirstY), 2)));
		}
	};
public:

	Processing();
	~Processing();

	void doMainLoop();

	void setMapChipDataCheck(int roomNumMax, int argSide, int range);
	int getStartPositionX(int range, int index, const std::vector<Map>& mapChip, int argSide, int nowSplit);
	int getStartPositionY(int range, int index, const std::vector<Map>& mapChip, int argSide, int nowSplit);
	void setMapChip(int firstX, int firstY, int index,const std::vector<Map> map);
	void setRandomPassagePosition(int range, int argSide);
	Position getRandomSpacePosition(int range,int argSide, int firstX, int firstY);
	void setConsolidatedPassage();
	bool setWayConsolidatedList(const std::string& way, std::vector<struct Position>* wayPos);
	bool setDistanceConsolidatedList(int comparisonIndex,const std::vector<struct Position>& wayPos, std::vector<struct Data>* disPos);

	int getNeaIndexrDistancePos(int comparisonIndex, const std::vector<struct Data>& disPos);
	void consolidatedPassage(int index, const std::vector<struct Data>& disPos);
	void setConsolidated(int firstPos, int endPos,int posX, int posY);
};