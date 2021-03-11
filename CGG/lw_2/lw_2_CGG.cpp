#include <iostream>

using namespace std;

class Dot {
private:
	int x;
	int y;
public:
	int X() { return x; }
	int Y() { return y; }
	Dot(int value1, int value2)
	{
		x = value1;
		y = value2;
	}
};

int main()
{
	cout << "Dot coordinates are: \n";
	Dot A(3, 3);
	cout << A.X() <<"\t" << A.Y();
	return 0;
}