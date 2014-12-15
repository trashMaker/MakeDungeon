#include <conio.h>
#include <cstdio>

int main(){
	while (1){
		if (_kbhit()){
			int buf = getch();

			printf("%c %0x\n", buf, buf);
		}
	}
}