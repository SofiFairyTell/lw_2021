#include <iostream>

using namespace std;

/*TODO
1. Создать точки треугольника ABC с координамами в виде x,y
2. Обеспечить ввод точки пользователем.

*/


class Dot {
private:
	int x;
	int y;
public:
    //Getters for X and Y
	int X() { return x; }
	int Y() { return y; }

    //Setters for X and Y
	void setX(int value){x = value;}
    void setY(int value){y = value;}     
    int SetCoords()
    {
        return 0;
    }
};

int main()
{

	return 0;
}