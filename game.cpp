#include <iostream>
#include <conio.h>
#include <windows.h>
#include <dos.h>
#include <time.h> // manipulacija time i date
#include "define.h"
#include "element.h"
#include "snake.h"

int main(){
	setcursor(0,0); // pozicija kursora
	srand( (unsigned)time(NULL)); // SEED ovisno o vremenu - bez toga - random ce biti uvijek isti - sto znaci da ce vocka uvijek biti na istome mjestu i imati isti pattern

	Snake snake; //objekt zmija
	char op = 'l';
	do{
		if(kbhit()){ // primamo slovo - spremamo ga u varijablu op
			op = getch();
		}
		switch(op){
			case 'h':
			case 'H':
				DIFF = 50;
				break;

			case 'J':
			case 'j':
				DIFF = 10;
				break;

			case 'K':
			case 'k':
				DIFF = 0.1;
				break;

			case 'w':
			case 'W':
				snake.TurnUp();
				break;
			
			case 's':
			case 'S':
				snake.TurnDown();
				break;
			
			case 'a':
			case 'A':
				snake.TurnLeft();
				break;
			
			case 'd':
			case 'D':
				snake.TurnRight();
				break;
		}
		snake.Move();
	}while(op != 'e');
	
	return 0;
}