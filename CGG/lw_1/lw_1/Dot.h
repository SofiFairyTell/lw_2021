#include <iostream>
#include <cmath>
#include <string>

#pragma once

class Dot
{

	private:
		float x;
		float y;
	public:
		//getters
		float X() { return x; }
		float Y() { return y; }
		//setters
		void setX(float value) { x = value; }
		void setY(float value) { y = value; }

		void setCoordinates(Dot& dot)
		{
			float value1, value2;
			std::cout << "Enter the coordinates: \n";
			std::cin >> value1; 
			std::cout << "\n"; 
			std::cin >> value2;
			dot.setX(value1);
			dot.setY(value2);
		}
};

class Vector
{
private:
	float x;
	float y;
public:
	float X() { return x; }
	float Y() { return y; }

	void setX(float value) { x = value; }
	void setY(float value) { y = value; }

	void set_coordinats(Dot& dot1, Dot& dot2)
	{
		setX(dot2.X() - dot1.X());
		setY(dot2.Y() - dot1.Y());
	}

	double VectorLength()
	{
		double result = sqrt(pow(X(), 2) + pow(Y(), 2));
		return result;
	}
};

bool EqualDot(Dot& first, Dot& second)
{
	std::string answer;
	if (first.X() == second.X() && first.Y() == second.Y())
	{
		return true;
		std::cout << first.X() << first.Y() << "\t" << second.X() << second.Y();
	}
	else
		return false;
}


