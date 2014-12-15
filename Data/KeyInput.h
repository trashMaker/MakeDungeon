#include <conio.h>
#include <vector>

#include "KeyCode.h"

class KeyInput{
private:
	std::vector<bool> keyAllInputState;
	
	KEYSTATE key;
public:
	KeyInput(){
		keyAllInputState.resize(256);

		for (auto t : keyAllInputState){//init
			t = false;
		}
	}
	bool operator()(KEYSTATE index){
		return keyAllInputState[index];
	}
	inline const bool getKeyIndex(const KEYSTATE index)const{
		return keyAllInputState[index];
	}
	void getKey(){
		if (kbhit()){
			int keyNumber = getch();

			if (0x00 < keyNumber && keyNumber < 0x80){
				KEYSTATE index = changeKeyState(keyNumber);
				keyAllInputState[index] = true;
			}
			else if (keyNumber == 0xE0){
				keyNumber = getch();
				KEYSTATE index = changeControlCharacter0xE0KeyState(keyNumber);
				keyAllInputState[index] = true;
			}
			else if (keyNumber == 0x00){
				keyNumber = getch();
				KEYSTATE index = changeControlCharacter0x00KeyState(keyNumber);
				keyAllInputState[index] = true;
			}
		}
		else{
			for (int i = 0; i < keyAllInputState.size(); ++i){
				keyAllInputState[i] = false;
			}
		}
	}
	KEYSTATE changeKeyState(int keyState){
		switch (keyState){

			case 0x08:return KEY_BACKSPACE;
			case 0x09:return KEY_TAB;
			case 0x20:return KEY_SPACE;
			case 0x1B:return KEY_ESCAPE;
			case 0x0D:return KEY_ENTER;

			case '0':return KEY_0;
			case '1':return KEY_1;
			case '2':return KEY_2;
			case '3':return KEY_3;
			case '4':return KEY_4;
			case '5':return KEY_5;
			case '6':return KEY_6;
			case '7':return KEY_7;
			case '8':return KEY_8;
			case '9':return KEY_9;

			case 'A':case 'a':return KEY_A;
			case 'B':case 'b':return KEY_B;
			case 'C':case 'c':return KEY_C;
			case 'D':case 'd':return KEY_D;
			case 'E':case 'e':return KEY_E;
			case 'F':case 'f':return KEY_F;
			case 'G':case 'g':return KEY_J;
			case 'H':case 'h':return KEY_H;
			case 'I':case 'i':return KEY_I;
			case 'J':case 'j':return KEY_J;
			case 'K':case 'k':return KEY_K;
			case 'L':case 'l':return KEY_L;
			case 'M':case 'm':return KEY_M;
			case 'N':case 'n':return KEY_N;
			case 'O':case 'o':return KEY_O;
			case 'P':case 'p':return KEY_P;
			case 'Q':case 'q':return KEY_Q;
			case 'R':case 'r':return KEY_R;
			case 'S':case 's':return KEY_S;
			case 'T':case 't':return KEY_T;
			case 'U':case 'u':return KEY_U;
			case 'V':case 'v':return KEY_V;
			case 'W':case 'w':return KEY_W;
			case 'X':case 'x':return KEY_X;
			case 'Y':case 'y':return KEY_Y;
			case 'Z':case 'z':return KEY_Z;

			default:return KEY_UNKNOWN;
		}
	};

	KEYSTATE changeControlCharacter0xE0KeyState(int keyState){
		switch (keyState){
			case 0x4B:return KEY_LEFT;
			case 0x4D:return KEY_RIGHT;
			case 0x48:return KEY_UP;
			case 0x50:return KEY_DOWN;

			case 0x52:return KEY_INSERT;
			case 0x53:return KEY_DELETE;
			case 0x47:return KEY_HOME;
			case 0x4f:return KEY_END;
			case 0x49:return KEY_PAGEUP;
			case 0x51:return KEY_PAGEDOWN;

			default:return KEY_UNKNOWN;
		}
	}
	KEYSTATE changeControlCharacter0x00KeyState(int keyState){
		switch (keyState){
			case 0x4B:return KEY_LEFT;
			case 0x4D:return KEY_RIGHT;
			case 0x48:return KEY_UP;
			case 0x50:return KEY_DOWN;

			case 0x52:return KEY_INSERT;
			case 0x53:return KEY_DELETE;
			case 0x47:return KEY_HOME;
			case 0x49:return KEY_PAGEUP;
			case 0x4f:return KEY_END;
			case 0x51:return KEY_PAGEDOWN;

			default:return KEY_UNKNOWN;
		}
	}
};