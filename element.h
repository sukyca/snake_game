#ifndef ELEMENT_H
#define ELEMENT_H

extern int MAX_X;  // granica po x
extern int MAX_Y; // granica po y

class Element{
	private:
		int y; //velicina grida
		int x; //velicina grida
	public:
		Element();

		Element(int x, int y);

		void SetElement(int x, int y);

		int GetX();

		int GetY();

		void Up();

		void Down();

		void Left();

		void Right();

		void Draw(char ch='O');

		void CopyPosition(Element * p);

		int Equal(Element * p);

		void Debug();
};

#endif