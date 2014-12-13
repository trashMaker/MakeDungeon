#pragma once

#include "Mover.h"
#include "Common.h"

class Character :public Mover{
protected:
	int hp;
public:
	Character(const std::string& fileName = "CharactorData", const std::string& format = ".txt", int _x = 0, int _y = 0);
	void setHp(int argHp){
		hp = argHp;
	};
	int getHp(){
		return hp;
	}
	
	virtual ~Character();
	virtual void draw();

};