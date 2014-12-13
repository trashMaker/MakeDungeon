#pragma once
#include <vector>
#include <random>

class Random{
private:
	std::random_device rd;

	std::vector<int> randomTable;

	struct PARAMETER{
		int min;
		int max;
		PARAMETER(int argMin, int argMax){
			this->min = argMin;
			this->max = argMax;
		}
	};
	PARAMETER parameter;
public:
	const int getRandom(int min, int max)const throw();

	void setParameterMinMax(int argMin, int argMax)throw();
	void clearRandomTable()throw();
	int getRandomTableSize()throw();
	bool checkRandomTable(int rand)throw();

	void setRandomTableDifferentNumberPossibleIsEntered(int tableNum = 0)throw();
	void setRandomTableSameNumberPossibleIsEntered(int tableNum = 0)throw();

	void getRandomTable(std::vector<int>* inputRandTable)throw();

	void sameLump(int setMin, int setMax, std::vector<int>* randTable, int tableNum = 0);
	void diffLump(int setMin, int setMax, std::vector<int>* randTable, int tableNum = 0);

	void prepareLump(int setMin, int setMax, std::vector<int>* randTable, int value, int randInValueNum, int tableNum = 0);

	void setRandomTableValueSetRandInValueNum(int value, int randInValueNum, int tableNum);

	Random(int min = 0, int max = 0);
	~Random();
};