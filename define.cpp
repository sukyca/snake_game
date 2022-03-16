#include "define.h"
#include <windows.h> // funkcionalnosti poput HANDLE, COORD etc.

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // Definiramo standarni output device. STD_OUTPUT_HANDLE je aktivni buffer za console screen https://docs.microsoft.com/en-us/windows/console/console-screen-buffers
COORD CursorPosition; // definira koordinate karaktera unutar konzole

void gotoxy(int x, int y){
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition); // postavlja poziciju kursora u konzoli
}
void setcursor(bool visible, DWORD size){ // set bool visible = 0 - invisible, bool visible = 1 - visible

	if(size == 0) 
	{
		size = 20;	// default velicina kursora
	}
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor); // Postavlja velicinu i vidljivost kursora za definiranu konzolu
}