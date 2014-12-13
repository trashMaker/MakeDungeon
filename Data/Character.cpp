#include "Character.h"
#include <iostream>
#include <Windows.h>
Character::Character(const std::string& fileName, const std::string& format, int _x, int _y) :Mover(_x, _y){
	std::string readFileName = "../CharactorData/" + fileName;
	std::vector<std::string> CharctorData = readFileData(readFileName, format);
	setHp(parseProperty(CharctorData, "HP"));
}
Character::~Character(){

}
void Character::draw(){
	std::cout << getHp() << std::endl;
}