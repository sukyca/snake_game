#include <iostream>
#include <conio.h> // kbhit, getch etc.
#include <windows.h> // funkcionalnosti poput HANDLE, COORD etc.
#include <dos.h> //DISK operating system - Sleep
#include <time.h> // manipulacija time i date
#include <vector>

#define MAX_X 119 // granica po x
#define MAX_Y 29 // granica po y

int DIFF = 50; // tezina igre

using std::cout;
using std::endl;
using std::vector;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // Definiramo standarni output device. STD_OUTPUT_HANDLE je aktivni buffer za console screen https://docs.microsoft.com/en-us/windows/console/console-screen-buffers
COORD CursorPosition; // definira koordinate karaktera unutar konzole

void gotoxy(int x, int y){
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition); // postavlja poziciju kursora u konzoli
}
void setcursor(bool visible, DWORD size) // set bool visible = 0 - invisible, bool visible = 1 - visible
{
	if(size == 0) 
	{
		size = 20;	// default velicina kursora
	}
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor); // Postavlja velicinu i vidljivost kursora za definiranu konzolu
}

class Element{
	private:
		int y; //velicina grida
		int x; //velicina grida
	public:
		Element(){
			x = y = 10;
		} 
		Element(int x, int y){
			this -> y = y;
			this -> x = x;	
		}
		void SetElement(int x, int y){
			this -> x = x;
			this -> y = y;
		}
		int GetX(){
			return x;
		}
		int GetY(){
			return y;
		}
		void Up(){
			y--;
			if( y < 0 )
				y = MAX_Y;
		}
		void Down(){
			y++;
			if( y > MAX_Y )
				y = 0;
		}
		void Left(){
			x--;
			if( x < 0 )
				x = MAX_X;
		}
		void Right(){
			x++;
			if( x > MAX_X )
				x = 0;
		}
		void Draw(char ch='O'){
			gotoxy(x,y);
			cout<<ch;
		}
		void CopyPosition(Element * p){ // Svaki element zmije ima svoj pokazivac 'p' - argument -> polje
			p->x = x;
			p->y = y;
		}
		int Equal(Element * p){
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
		vector<Element*> snakecell; // vektor polje zmije
		int size; // velicina zmije
		char dir; // smjer zmije - up, down, left, right
		Element fruit; // objekt vocka
		int state; // stanje zmije - moze biti aktivna ili neaktivna
		int started; // stanje igre - moze biti pokrenuta ili cekamo key za pokrenuti igru
		int blink; // flag za semaphore
	public:
		Snake(){
			size = 1; // default velicina zmije
			snakecell.push_back(new Element(20,20)); // dodajemo novi element u polje - u ovom slucaju glavu
			fruit.SetElement(rand()%MAX_X, rand()%MAX_Y); // postavljamo vocku na random koordinate - mod sa maks. x i y
			state = 0; // default - zmija nije aktivna
			started = 0; // default - igra nije zapoceta
		}
		void AddCell(int x, int y){ // dodajemo +1 na rep(size) nakon collisiona - na kraj liste
			size++;
			snakecell.push_back(new Element(x,y));
		}
		void TurnUp(){ //funkcije koje mijenjaju smjer
			if( dir!='s' )
			dir = 'w'; // w - smjer gore
		}
		void TurnDown(){ 
			if( dir!='w' )
			dir = 's'; // s - smjer dole
		}
		void TurnLeft(){ 
			if( dir!='d' )
			dir = 'a'; // a - smjer lijevo
		}
		void TurnRight(){
			if( dir!='a' )
			dir = 'd'; // d - smjer desno
		}
		void Welcome(){
			SetConsoleTextAttribute(console,10); // SetConsoleTextAttribute omogucava odabir razlicitih stilova za background i foreground
			// https://www.asciiart.eu/animals/reptiles/snakes?fbclid=IwAR2FofLi0I40lY1Dr0ahWiTaRB1qdsIdyQbSl5Kg5CmeX-rer0zey0DkGSg
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
			system("cls"); // clear screen
			cout << "SCORE: " <<size; // pratimo score
			
			if( state == 0 ){ // menu
				if( !started ){
					Welcome();
					cout<<"\n\nPress any key to start";
					cout<<"\n\n--CONTROLS--";
					cout<<"\n\nw - up \t\th - change difficulty to Easy";
					cout<<"\n\ns - down \tj - change difficulty to Normal";
					cout<<"\n\na - left \tk - change difficulty to Hard";
					cout<<"\n\nd - right";
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
			
			for(int i=size-1; i>0; i--){ // zmijino tijeo prati glavu
				snakecell[i-1]->CopyPosition(snakecell[i]);
			}

			switch(dir){ // ponasanje glave zmije
				case 'w':
					snakecell[0]->Up();
					break;
				case 's':
					snakecell[0]->Down();
					break;
				case 'a':
					snakecell[0]->Left();
					break;
				case 'd':
					snakecell[0]->Right();
					break;
			}
			
			if( SelfCollision() ) // nakon sudara state postavljamo na 0 - zmija neaktivna
				state = 0;
				
			if( fruit.GetX() == snakecell[0]->GetX() && fruit.GetY() == snakecell[0]->GetY()){ // zmija pojede vocku
				AddCell(0,0);
				fruit.SetElement(rand()%MAX_X, rand()%MAX_Y); 	
			}
			
			for(int i=0; i<size; i++) // crtanje zmije
				snakecell[i]->Draw();
				
			SetConsoleTextAttribute(console,10); 
			if( !blink ) // semafor - svaka druga iteracija
				fruit.Draw('Q'); // crtanje vocke
			blink = !blink;
			SetConsoleTextAttribute(console,10);
			
			//Debug();
			
			Sleep(DIFF); // DIFF u ms - vrijeme koraka - brzina izvodjenja
		}
		int SelfCollision(){ // Zmija ugrize samu sebe
			for(int i=1; i<size; i++)
				if( snakecell[0]->Equal(snakecell[i]) ) // usporedujemo je li pozicija glave jednaka nekoj poziciji tijela/repa
					return 1; // true
			return 0;
		}
		void Debug(){
			for( int i=0; i<size; i++){
				snakecell[i]->Debug();
			}
		}
};

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