#include <iostream>
#include <conio.h> // kbhit, getch
#include <dos.h> //DISK operating system - Sleep
#include <vector>
#include "element.h"
#include "define.h"
#include "snake.h"

using std::cout;
using std::endl;
using std::vector;

int DIFF = 25; // tezina 


Snake::Snake(){
    size = 1; // default velicina zmije
    snakecell.push_back(new Element(20,20)); // dodajemo novi element u polje - u ovom slucaju glavu
    fruit.SetElement(rand()%MAX_X, rand()%MAX_Y); // postavljamo vocku na random koordinate - mod sa maks. x i y
    state = 0; // default - zmija nije aktivna
    started = 0; // default - igra nije zapoceta
}
void Snake::AddCell(int x, int y){ // dodajemo +1 na rep(size) nakon collisiona - na kraj liste
    size++;
    snakecell.push_back(new Element(x,y));
}
void Snake::TurnUp(){ //funkcije koje mijenjaju smjer
    if( dir!='s' )
    dir = 'w'; // w - smjer gore
}
void Snake::TurnDown(){ 
    if( dir!='w' )
    dir = 's'; // s - smjer dole
}
void Snake::TurnLeft(){ 
    if( dir!='d' )
    dir = 'a'; // a - smjer lijevo
}
void Snake::TurnRight(){
    if( dir!='a' )
    dir = 'd'; // d - smjer desno
}
void Snake::Welcome(){
    SetConsoleTextAttribute(console,10); // SetConsoleTextAttribute omogucava odabir razlicitih stilova za background i foreground
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
void Snake::Move(){
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
int Snake::SelfCollision(){ // Zmija ugrize samu sebe
    for(int i=1; i<size; i++)
        if( snakecell[0]->Equal(snakecell[i]) ) // usporedujemo je li pozicija glave jednaka nekoj poziciji tijela/repa
            return 1; // true
    return 0;
}
void Snake::Debug(){
    for( int i=0; i<size; i++){
        snakecell[i]->Debug();
    }
}
