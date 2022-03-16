#include <iostream>
#include "define.h"
#include "element.h"

int MAX_X = 119; // granica po x
int MAX_Y = 29; // granica po y

using std::cout;

Element::Element(){
    x = y = 10;
} 

Element::Element(int x, int y){
    this -> y = y;
    this -> x = x;	
}
void Element::SetElement(int x, int y){
    this -> x = x;
    this -> y = y;
}
int Element::GetX(){
    return x;
}
int Element::GetY(){
    return y;
}
void Element::Up(){
    y--;
    if( y < 0 )
        y = MAX_Y;
}
void Element::Down(){
    y++;
    if( y > MAX_Y )
        y = 0;
}
void Element::Left(){
    x--;
    if( x < 0 )
        x = MAX_X;
}
void Element::Right(){
    x++;
    if( x > MAX_X )
        x = 0;
}
void Element::Draw(char ch/*='O'*/){ // funkcija za crtanje
    gotoxy(x,y);
    cout<<ch;
}
void Element::CopyPosition(Element * p){ // Svaki element zmije ima svoj pokazivac 'p' - argument -> polje
    p->x = x;
    p->y = y;
}
int Element::Equal(Element * p){ // funkcija koju kasnije koristimo kao usporedjivac
    if( p->x == x && p->y ==y )
        return 1;
    return 0;
}
void Element::Debug(){
    cout<<"("<<x<<","<<y<<") ";
}
