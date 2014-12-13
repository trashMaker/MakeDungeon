#pragma once

class Mover{
protected:
	int x, y;
public:
	inline int getX(){
		return x;
	}
	inline int getY(){
		return y;
	}
	void setX(int _x){
		x = _x;
	}
	void setY(int _y){
		y = _y;
	}
	Mover(int _x, int _y) :
		x(_x), y(_y){
		//this->x; //‚±‚Á‚¿‚àok
		//this->y;
	}

	virtual inline void Move(int _x, int _y){
		setX(this->x + _x);
		setY(this->y + _y);
	};
};