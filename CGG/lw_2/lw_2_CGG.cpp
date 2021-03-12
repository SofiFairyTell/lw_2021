#include <iostream>
#include<cmath>

#define PI 3.1415

using namespace std;
// To do 
//Определить принадлежность через Треугольники
// Определеить принадлежность через Барицентрические координаты
class Dot {
private:
	int x;
	int y;
public:
	//getters
	int X() { return x; }
	int Y() { return y; }
	//setters
	void setX(int value) { x = value; }
	void setY(int value) { y = value; }

	void setCoordinates(Dot &dot)
	{
		int value1, value2;
		cout << "Enter the coordinates: \n";
		cin >> value1; cout << "\t"; cin >> value2;
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
		setX (dot2.X() - dot1.X());
		setY ( dot2.Y() - dot1.Y());
	}

	double VectorLength()
	{
		double result = sqrt( pow(X(),2)+pow(Y(),2));
		return result;
	}
};


bool EqualDot(Dot &first, Dot &second)
{
	string answer;
	if (first.X() == second.X() && first.Y() == second.Y())
	{
		return true;
		cout << first.X() << first.Y() << "\t" << second.X() << second.Y();
	}
	else
		return false;
}


//внутри, снаружи, на границе
	// P - ее местоположение нужно определить
	//  A, B,C - координаты вершин
	// Формула: a*b = |a||b| cos y , 
	// где a и b - векторы , y - угол между ними
	// Вектора: AB, BC, CA - для треугольника
	// |AB| = sqrt((B.x - A.x)^2 + (B.y - A.y)^2 )
	// Вычисление: 
		//cos α = 	(a·b)/ |a|·|b| ~ 0,1 or 0,96 -> arcos a ~ 30` 
		//у нас для angle APC вектор a = P.x - A.x
		// Пример расчета: APB =arcos( (-0.4*0.6 + 4.3*-1.6) / (1.71 * 4.32 ) )= arcos((-7.12 / 7.37)) = 165*93`
	// Условия завершения: 
	// Сумма углов: 
		//  = 360 - точка внутри и на границе
		// != 360 - вне треугольника
	// Углы: 
		// = 180 - точка на границе
	// Совпадение координат 
		// Если P.x = A.x и P.y = A.y, то P - совпадает с A, 
		// answer = границе треугольника
string Triangle_method(Dot& A, Dot& B, Dot& C, Dot& P )
{
	string answer;
	
	if(EqualDot(P,B) == true || EqualDot(P,A)== true || EqualDot(P,C)==true)
	{
		cout<<"Точка совпала с одной из вершин"<<endl;
	}
	else
	{
		//координаты векторов

		Vector vector_pa = Vector();
		Vector vector_pb = Vector();
		Vector vector_pc = Vector();

		vector_pa.set_coordinats(P, A);
		vector_pb.set_coordinats(P, B);
		vector_pc.set_coordinats(P, C);

		// углы
		float angle_apb = (acos((vector_pa.X()*vector_pb.X()+vector_pa.Y()*vector_pb.Y())/(vector_pa.VectorLength()*vector_pb.VectorLength())) *180)/ PI ; //в градусах
		float angle_bpc = (acos((vector_pb.X()*vector_pc.X()+vector_pb.Y()*vector_pc.Y())/(vector_pb.VectorLength()*vector_pc.VectorLength())) *180)/ PI ; //в градусах
		float angle_apc = (acos((vector_pa.X()*vector_pc.X()+vector_pa.Y()*vector_pc.Y())/(vector_pa.VectorLength()*vector_pc.VectorLength())) *180)/ PI ; //в градусах
		// сумма углов
		float sum_angle = angle_apb + angle_bpc + angle_apc;
		if (sum_angle != 360)
		{
			cout << "Точка вне обозначенной области";
		}
		else
			cout << "Точка внутри обозначенной области";

	}

};
string Baricenter_menthod()
{
	// P. = aA + bB + cC where  (a,b,c) - барицентрические координаты
	// P = aA + bB + cC where  (a,b,c) - барицентрические координаты
	
	//(a+b+c=1) and a >=0 and b >=0 and c >=0 (*)
	
	// Выходные данные:
	//  Если * верно и хотя бы одна координат (a, b,c) = 0, то на границе
	//  Если * верно и хотя бы одна координат (a, b,c) = 1, то совпадение с вершиной
	// 	Если * не верно, то вне треугольника

	string answer;
	return answer;
}



int main()
{
	cout << "---------------START--------------------"; 
	cout << "Enter the coordinates for the following dots:\n";
	Dot A = Dot();
	Dot B = Dot();
	Dot C = Dot();
	Dot P = Dot(); // Точка которую будем проверять
	cout << "A";
	cout << "B";
	cout << "C";
	cout << "P";
	return 0;
}