#include <iostream>
#include <conio.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;

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
};

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
