#include <iostream>
#include <conio.h>
#include <windows.h>
#include <dos.h>
#include <time.h>
#include <vector>

#define MAXFRAMEX 119
#define MAXFRAMEY 29

int DIFF = 100;

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void gotoxy(int x, int y){
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}
void setcursor(bool visible, DWORD size) // set bool visible = 0 - invisible, bool visible = 1 - visible
{
	if(size == 0) //velicina slova
	{
		size = 50;	// default cursor size Changing to numbers from 1 to 20, decreases cursor width
	}
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}

class Point{
	private:
		int y; //velicina grida
		int x; //velicina grida
	public:
		Point(){
			x = y = 10;
		} 
		Point(int x, int y){
			this -> y = y;
			this -> x = x;	
		}
		void SetPoint(int x, int y){
			this -> x = x;
			this -> y = y;
		}
		int GetX(){
			return x;
		}
		int GetY(){
			return y;
		}
		void MoveUp(){
			y--;
			if( y < 0 )
				y = MAXFRAMEY;
		}
		void MoveDown(){
			y++;
			if( y > MAXFRAMEY )
				y = 0;
		}
		void MoveLeft(){
			x--;
			if( x < 0 )
				x = MAXFRAMEX;
		}
		void MoveRight(){
			x++;
			if( x > MAXFRAMEX )
				x = 0;
		}
		void Draw(char ch='O'){
			gotoxy(x,y);
			cout<<ch;
		}
		void Erase(){
			gotoxy(x,y);
			cout<<" ";
		}
		void CopyPos(Point * p){ // Svaki element zmije ima svoj pokazivac 'p' - argument -> polje
			p->x = x;
			p->y = y;
		}
		int IsEqual(Point * p){
			if( p->x == x && p->y ==y )
				return 1;
			return 0;
		}
		void Debug(){
			cout<<"("<<x<<","<<y<<") ";
		}
};

class Snake{
	private:
		//Point * cell[MAXSNAKESIZE]; // array of points to represent snake - povezana lista
		vector<Point*> snakecell;
		int size; // current size of snake
		char dir; // current direction of snake
		Point fruit; 
		int state; // bool representing state of snake i.e. living, dead
		int started;
		int blink; // fruit blink
	public:
		Snake(){
			size = 1; // default size
			//cell[0] = new Point(20,20); // 20,20 is default position - dinamicna alokacija memorije
			snakecell.push_back(new Point(20,20));
			// for( int i=1; i<MAXSNAKESIZE; i++){
			// 	cell[i] = NULL; // postavljamo sva ostala polja liste/vektora na NULL vrijednost
			// }
			fruit.SetPoint(rand()%MAXFRAMEX, rand()%MAXFRAMEY); // postavljamo vocku na random koordinate
			state = 0;
			started = 0;
		}
		int GetScore(){
			return size;
		}
		void AddCell(int x, int y){ // dodajemo +1 na rep nakon collisiona - na kraj liste
			//cell[size++] = new Point(x,y);
			size++;
			snakecell.push_back(new Point(x,y));
		}
		void TurnUp(){ //funkcije koje mijenjaju smjer
			if( dir!='s' )
			dir = 'w'; // w is control key for turning upward
		}
		void TurnDown(){ 
			if( dir!='w' )
			dir = 's'; // s is control key for turning downward
		}
		void TurnLeft(){ 
			if( dir!='d' )
			dir = 'a'; // a is control key for turning left
		}
		void TurnRight(){
			if( dir!='a' )
			dir = 'd'; // d is control key for turning right
		}
		void WelcomeScreen(){
			SetConsoleTextAttribute(console,15);
			cout<<"\n            /^\\/^\\                                             ";
			cout<<"\n          _|__|  O|                                              ";
			cout<<"\n \\/     /~     \\_/ \\                                          ";
			cout<<"\n  \\____|__________/  \\                                         ";
			cout<<"\n         \\_______      \\                                       ";
			cout<<"\n                 `\\     \\                 \\                   ";
			cout<<"\n                   |     |                  \\                   ";
			cout<<"\n                  /      /                    \\                 ";
			cout<<"\n                 /     /                       \\\\              ";
			cout<<"\n               /      /                         \\ \\            ";
			cout<<"\n              /     /                            \\  \\          ";
			cout<<"\n            /     /             _----_            \\   \\        ";
			cout<<"\n           /     /           _-~      ~-_         |   |          ";
			cout<<"\n          (      (        _-~    _--_    ~-_     _/   |          ";
			cout<<"\n           \\      ~-____-~    _-~    ~-_    ~-_-~    /          ";
			cout<<"\n             ~-_           _-~          ~-_       _-~            ";
			cout<<"\n                ~--______-~                ~-___-~               ";
		}
		void Move(){
			// Clear screen
			system("cls");
			cout << "SCORE: " <<size;
			
			if( state == 0 ){
				if( !started ){
					WelcomeScreen();
					cout<<"\n\nPress any key to start";
					cout<<"\n\nh - easy";
					cout<<"\n\nj Medium";
					cout<<"\n\nk Hard";
					getch();
					started = 1;
					state = 1; 
				}else{
					cout<<"\nGame Over"<<endl;
					cout<<"\nScore: "<< size <<endl;
					cout<<"\nPress any key to start";
					getch();
					state = 1;
					size = 1;	
				}
			}
			
			// making snake body follow its head
			for(int i=size-1; i>0; i--){
				//snakecell.push_back(new Point(x,y));
				snakecell[i-1]->CopyPos(snakecell[i]);
				
			}

			
			// turning snake's head
			switch(dir){
				case 'w':
					snakecell[0]->MoveUp();
					break;
				case 's':
					snakecell[0]->MoveDown();
					break;
				case 'a':
					snakecell[0]->MoveLeft();
					break;
				case 'd':
					snakecell[0]->MoveRight();
					break;
			}
			
			if( SelfCollision() )
				state = 0;
				
			
				
			
			// Collision with fruit
			if( fruit.GetX() == snakecell[0]->GetX() && fruit.GetY() == snakecell[0]->GetY()){
				AddCell(0,0);
				fruit.SetPoint(rand()%MAXFRAMEX, rand()%MAXFRAMEY); 	
			}
			
			//drawing snake
			for(int i=0; i<size; i++)
				snakecell[i]->Draw();
				
			SetConsoleTextAttribute(console,242); //font - velicina 
			if( !blink ) // semafor - svaka druga iteracija
				fruit.Draw('°');
			blink = !blink;
			SetConsoleTextAttribute(console,252);
			
			//Debug();
			
			Sleep(DIFF); // DIFF u ms - vrijeme koraka 
		}
		int SelfCollision(){ // Zmija ugrize samu sebe
			for(int i=1; i<size; i++)
				if( snakecell[0]->IsEqual(snakecell[i]) ) // Usporedujemo je li pozicija glave jednaka nekoj poziciji tijela/repa
					return 1;
			return 0;
		}
		void Debug(){
			for( int i=0; i<size; i++){
				snakecell[i]->Debug();
			}
		}
};

int main(){
	//random no generation
	setcursor(0,0);
	srand( (unsigned)time(NULL)); // SEED ovisno o vremenu - bez toga - random ce biti uvijek isti - sto znaci da ce vocka uvijek biti na istome mjestu
	
	// Testing snake 
	Snake snake;
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

// THE END