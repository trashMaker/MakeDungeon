#include <conio.h>
#include <vector>
class KeyInput{
private:
	std::vector<bool> keyAllInputState;
public:
	KeyInput(){
		keyAllInputState.resize(256);
	}
	void getKey(){
		if (kbhit()){
			getch();
		}
	}
};