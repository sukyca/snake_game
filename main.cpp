#include <iostream>
#include <conio.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;

#define MAXSNAKESIZE 100

class Point
{
private:
    int x;
    int y;

public:
    Point()
    {
        x = y = 10;
    }

    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    void setPoint(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    int getX()
    {
        return x;
    }

    int getY()
    {
        return y;
    }

    void moveUp()
    {
        y--;
    }

    void moveDown()
    {
        y++;
    }

    void moveLeft()
    {
        x--;
    }

    void moveRight()
    {
        x++;
    }

    void Draw()
    {
        gotoxy(x, y);
        cout << "*";
    }

    void Erase()
    {
        gotoxy(x, y);
        cout << " ";
    }

    void Debug()
    {
        cout << " (" << x << ", " << y << ") ";
    }
};

int main()
{
    Point p(5, 20);

    p.Draw();

    return 0;
}
