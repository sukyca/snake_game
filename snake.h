#ifndef SNAKE_H
#define SNAKE_H

#include <iostream>
#include <conio.h> // kbhit, getch
#include <dos.h> //DISK operating system - Sleep
#include <vector>
#include "define.h"
#include "element.h"

using std::cout;
using std::endl;
using std::vector;

extern int DIFF;

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
		Snake();

		void AddCell(int x, int y);

		void TurnUp();

		void TurnDown();

		void TurnLeft();

		void TurnRight();

		void Welcome();

		void Move();

		int SelfCollision();

		void Debug();
};

#endif