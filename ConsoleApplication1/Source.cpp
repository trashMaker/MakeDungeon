#include <conio.h>
#include <cstdio>
int main(){
	while (1){
		if (_kbhit()){
			char buf = getch();

			printf("%c %d\n", buf, buf);
		}
	}
}