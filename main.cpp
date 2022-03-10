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

    void CopyPos(Point *p)
    {
        p->x = x;
        p->y = y;
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

class Snake
{
private:
    Point *cell[MAXSNAKESIZE];
    int size;
    char dir;

public:
    Snake()
    {
        size = 1;
        cell[0] = new Point(20, 20);
        for (int i = 1; i < MAXSNAKESIZE; i++)
        {
            cell[i] = NULL;
        }
    }

    void addCell(int x, int y)
    {
        cell[size++] = new Point(x, y);
    }

    void turnUp()
    {
        dir = 'w';
    }

    void turnDown()
    {
        dir = 's';
    }

    void turnLeft()
    {
        dir = 'a';
    }

    void turnRight()
    {
        dir = 'd';
    }

    void Move()
    {
        for (int i = size - 1; i < 0; i--)
        {
            cell[i]->CopyPos(cell[i - 1]);
        }

        switch (dir)
        {
        case 'w':
            cell[0]->moveUp();
            break;
        case 's':
            cell[0]->moveDown();
            break;
        case 'a':
            cell[0]->moveLeft();
            break;
        case 'd':
            cell[0]->moveRight();
            break;
        }
    }
};

int main()
{
    Point p(5, 20);

    p.Draw();

    return 0;
}
