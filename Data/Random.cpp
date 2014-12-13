#include "Random.h"
#include "Common.h"
//-----------------------------------
//処理 コンストラクタ
//引数 min 最小
//　　 max 最大
//返値 none
//-----------------------------------
Random::Random(int min, int max) :parameter(min, max){
	
};
//-----------------------------------
//処理 デストラクタ

//返値 none
//-----------------------------------
Random::~Random(){

}
//-----------------------------------
//処理 ランダム取得
//引数 min 最小
//　　 max 最大
//返値 int ランダム取得
//-----------------------------------
const int Random::getRandom(int min, int max)const throw(){
	std::mt19937 rng{ std::random_device()() };
	std::uniform_int_distribution<int> dist(min, max);
	return dist(rng);
}

//-----------------------------------
//処理 最小最大の設定
//引数 argMin int	最小
//　　 argMax int	最大
//返値 none
//-----------------------------------
void Random::setParameterMinMax(int argMin, int argMax)throw(){
	this->parameter.min = argMin;
	this->parameter.max = argMax;
}
//-----------------------------------
//処理 ランダムテーブルの初期化
//返値 none
//-----------------------------------
void Random::clearRandomTable()throw(){
	randomTable.clear();
}
//-----------------------------------
//処理 ランダムテーブルのサイズを返す
//返値 ランダムテーブルのサイズ
//-----------------------------------
int Random::getRandomTableSize()throw(){
	return randomTable.size();
}

//-----------------------------------
//処理 ランダムテーブルに追加されたデータと引数randが違うか確認
//引数 rand minmax範囲で取ったランダム値
//返値 異(true) 同(false) 
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
//処理 ランダムテーブルのテーブルが最大になるまで取得 必ず異なる数値がテーブルに入る
//引数 tableNum int	テーブルの数
//返値 none
//-----------------------------------
void Random::setRandomTableDifferentNumberPossibleIsEntered(int tableNum)throw(){

	int randMin = parameter.min;
	int randMax = parameter.max;
	int minmaxRange = (abs(randMax) + 1) - abs(randMin);
	ASSERT(minmaxRange >= tableNum, minmaxRange, STRING(minmaxRange), "テーブルの数と異なるランダムデータを入れるテーブルの数が一致していません");

	clearRandomTable();
	//tableNumがデフォルト引数の場合　
	if (tableNum == 0){
		tableNum = (abs(randMax) + 1) - abs(randMin);
	}

	////比較用に0番目に値追加
	//randomTable.push_back(getRandom(randMin, randMax));

	while (randomTable.size() != tableNum){
		int rand = getRandom(randMin, randMax);
		if (checkRandomTable(rand)){
			randomTable.push_back(rand);
		};	//異なった数が入ってるか確認して入れる	
	}
}
//-----------------------------------
//処理 ランダムテーブルのテーブルが最大になるまでランダム値を取得 (同じ数値でも可)
//引数 tableNum int	テーブルの数
//返値 none
//-----------------------------------
void Random::setRandomTableSameNumberPossibleIsEntered(int tableNum)throw(){

	int randMin = parameter.min;
	int randMax = parameter.max;

	clearRandomTable();
	//tableNumがデフォルト引数の場合　
	if (tableNum == 0){
		tableNum = (abs(randMax) + 1) - abs(randMin);
	}

	////比較用に0番目に値追加
	//randomTable.push_back(getRandom(randMin, randMax));

	while (randomTable.size() != tableNum){
		int rand = getRandom(randMin, randMax);
		randomTable.push_back(rand);
	}
}
//-----------------------------------
//処理 ランダムテーブルのテーブルをコピー 
//引数 inputRandTable std::vector<int>*	コピー用
//返値 none
//-----------------------------------
void Random::getRandomTable(std::vector<int>* inputRandTable)throw(){

	for (int index = 0; index < static_cast<int>(randomTable.size()); ++index){
		inputRandTable->push_back(randomTable[index]);
	}
}
//-----------------------------------
//処理 同じ値が入りうるランダム処理をまとめた
//引数 setMin		int	とりうる最小値
//　　 setMax		int とりうる最大値
//　　 randTable		std::vector<int>*　コピー用
//　　 tableNum		int ランダムテーブルの要素の数指定
//返値 none
//-----------------------------------
void Random::sameLump(int setMin, int setMax, std::vector<int>* randTable, int tableNum){
	setParameterMinMax(setMin, setMax);
	setRandomTableSameNumberPossibleIsEntered(tableNum);
	getRandomTable(randTable);
}
//-----------------------------------
//処理 異なる値が入りうるランダム処理をまとめた
//引数 setMin		int	とりうる最小値
//　　 setMax		int とりうる最大値
//　　 randTable		std::vector<int>*　コピー用
//　　 tableNum		int ランダムテーブルの要素の数指定
//返値 none
//-----------------------------------
void Random::diffLump(int setMin, int setMax, std::vector<int>* randTable, int tableNum){
	setParameterMinMax(setMin, setMax);
	setRandomTableDifferentNumberPossibleIsEntered(tableNum);
	getRandomTable(randTable);
}
//ある数値をランダム上で必ずその個数分は出すランダム
//-----------------------------------
//処理 valueの数値がrandInvalueNum個は確実に入るランダム処理をまとめた
//引数 setMin		int	とりうる最小値
//　　 setMax		int とりうる最大値
//　　 randTable		std::vector<int>*　コピー用
//　　 value			int 確実に入れたい要素
//　　 randInValueNum　int 確実に入れたい要素の数
//　　 tableNum		int ランダムテーブルの要素の数指定
//返値 none
//-----------------------------------
void Random::prepareLump(int setMin, int setMax, std::vector<int>* randTable, int value, int randInValueNum, int tableNum){
	setParameterMinMax(setMin, setMax);
	setRandomTableValueSetRandInValueNum(value, randInValueNum, tableNum);
	getRandomTable(randTable);
}

//ある数値をランダム上で必ずその個数分は出すランダム
//-----------------------------------
//処理 valueの数値がrandInvalueNum個は確実に入るランダム処理をまとめた
//引数 value		int	確実に入れたい要素
//　　 randInValueNum	int 確実に入れたい要素の数
//　　 tableNum　int ランダムテーブルの要素の数指定
//返値 none
//-----------------------------------
void Random::setRandomTableValueSetRandInValueNum(int value, int randInValueNum, int tableNum)throw(){

	ASSERT(tableNum >= randInValueNum, tableNum - randInValueNum, STRING(tableNum - randInValueNum), "追加したい要素の数よりテーブルの数が少ないです");
	//min maxマクロがあるからASSERTの引数内部に使えん。
	int randMin = parameter.min;
	int randMax = parameter.max;
	ASSERT(randMin <= value &&  value <= randMax, value, STRING(value), "追加したい要素が最大最小サイズの中に入っていません");

	int valueNum = 0;
	clearRandomTable();
	//tableNumがデフォルト引数の場合　
	if (tableNum == 0){
		tableNum = (abs(randMax) + 1) - abs(randMin);
	}

	////比較用に0番目に値追加
	//randomTable.push_back(getRandom(randMin, randMax));
	//if (randomTable.at(0) == value){
	//	++valueNum;
	//}
	/*
	while
	テーブルとサイズの数が一致するまでかつ、
	確実に入れる要素の残り　< 残り追加テーブルの数
	(確実に入れる要素数-今入ってる確実に入れる要素　< テーブル - ランダムテーブルのサイズ)`
	今入ってる要素数が確実に入れる要素数より低いなら
	min maxの範囲から普通に値を取得して、データを格納

	もしこの条件を抜けたとして、
	if
	確実に入れる要素の残り　< 残り追加テーブルの数なら
	残り全部を追加したい要素で追加
	else
	確実に入れる要素数<今入ってる確実に入れる要素数なら
	つまり確実に入れる要素はもう存在しないので
	あとは確実に入れる要素意外がランダムで来た場合のみ追加

	テーブルとサイズの数が一致するまでは
	その意味通りですが、必ずどっちかで引っかかるのでこれはいらん？
	*/

	while (randomTable.size() != tableNum &&
		randInValueNum - valueNum < tableNum - static_cast<int>(randomTable.size()) &&//確実に入れたい要素数-今入ってる確実に入れたい要素数
		valueNum < randInValueNum){

		int rand = getRandom(randMin, randMax);
		if (rand == value){
			++valueNum;
		}
		randomTable.push_back(rand);
	}
	//valueと同じ値を入れる
	if (valueNum < randInValueNum){
		while (valueNum != randInValueNum){
			randomTable.push_back(value);
			++valueNum;
		}
	}
	else{//valueと同じ値が入らないようにする
		while (randomTable.size() != tableNum){
			int rand = getRandom(randMin, randMax);
			if (rand != value){
				randomTable.push_back(rand);
			}
		}
	}
}