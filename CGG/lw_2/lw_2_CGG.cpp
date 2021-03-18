#include <iostream>
#include <cmath>
#include <string>
#include <vector>

#define PI 3.1415

using namespace std;
// To do 
//Определить принадлежность через Треугольники
// Определить принадлежность через Барицентрические координаты
class Dot {
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

	// void setCoordinates(Dot& dot)
	void setCoordinates(float value1, float value2)
	{
		// float value1, value2;
		// cout << "Enter the coordinates: \n";
		// cin >> value1; cout << "\n"; cin >> value2;
		setX(value1);
		setY(value2);
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
string Triangle_method(Dot& A, Dot& B, Dot& C, Dot& P)
{
	string answer;

	if (EqualDot(P, B) == true || EqualDot(P, A)== true || EqualDot(P, C) == true)
	{
		return "Dot is equal to one of the triangle's heights";
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
		float angle_apb = (acos((vector_pa.X() * vector_pb.X() + vector_pa.Y() * vector_pb.Y()) / (vector_pa.VectorLength() * vector_pb.VectorLength())) * 180) / PI; //в градусах
		float angle_bpc = (acos((vector_pb.X() * vector_pc.X() + vector_pb.Y() * vector_pc.Y()) / (vector_pb.VectorLength() * vector_pc.VectorLength())) * 180) / PI; //в градусах
		float angle_apc = (acos((vector_pa.X() * vector_pc.X() + vector_pa.Y() * vector_pc.Y()) / (vector_pa.VectorLength() * vector_pc.VectorLength())) * 180) / PI; //в градусах
		// сумма углов
		int sum_angle = angle_apb + angle_bpc + angle_apc;
		if (sum_angle != 360)
		{
			return "Dot is out of bounds";
		}
		else
			return "Dot is in the bounds";

	}

};
string Baricenter_method(Dot& A, Dot& B, Dot& C, Dot& P)
{
	string answer;
	// P = aA + b + cC where  (a,b,c) - барицентрические координаты
	// P.y = aA + bB + cC where  (a,b,c) - барицентрические координаты

	//(a+b+c=1) and a >=0 and b >=0 and c >=0 (*)

	// Выходные данные:
	//  Если * верно и хотя бы одна координат (a, b,c) = 0, то на границе
	//  Если * верно и хотя бы одна координат (a, b,c) = 1, то совпадение с вершиной
	// 	Если * не верно, то вне треугольника
	// denominate = (By - Cy)(Ax - Cx) + (Cx - Bx)(Ay - Cy)
	// a = (By - Cy)(Px-Cx) + (Cx-Bx)(Py-Cy) / denominate
	// b = (Cy - Ay)(Px - Cx) + (Ax - Cx)(Py - Cy)/ denominate
	// c = (Ay - By)(Px - Ax) + (Bx -  Ax)(Py - Ay)/ denominate
	float denominate = ((B.Y() - C.Y()) * (A.X() - C.X())) + ((C.X() - B.X()) * (A.Y() - C.Y()));

// float a = 0.6 int a = 0
	float a = (((B.Y() - C.Y()) * (P.X() - C.X())) + ((C.X() - B.X()) * (P.Y() - C.Y()))) / denominate;
	float b = (((C.Y() - A.Y()) * (P.X() - C.X())) + ((A.X() - C.X()) * (P.Y() - C.Y()))) / denominate;
	float c = (((A.Y() - B.Y()) * (P.X() - C.X())) + ((B.X() - A.X()) * (P.Y() - A.Y()))) / denominate;


	int check_sum = (abs(a) + abs(b) + abs(c)); //без abs вернет 0, т.к. отрицательные значения в весах

	if (check_sum == 1 && (abs(a) >= 0 && abs(b) >= 0 && abs(c) >= 0))
	{
		answer = "The dot is in the triangle";
		// уточнение, т.е. где именно она в треугольнике
		if (a == 1 || b == 1 || c == 1)
		{
			answer += "\nGiven dot is equal to one of the triangle's heights";
		}
		else
			if (a == 0 || b == 0 || c == 0)
			{
				answer += "\nThe dot is on the border";
			}
			else
				answer = "\nGiven dot in the triangle";


		return answer;
	}
	else
		answer = "\nGiven dot is not in the triangle";
	
	return answer;
}

string Polygon_method(vector<Dot> dots, Dot& P)
{
	string answer;
	/**
	 
	  
	* inPolygonTrue = true; для проверки при совпадении на границе
	* Следовательно: если из какой-нибудь вершины многоугольника провести все возможные диагонали,
	* то они разделят многоугольник на треугольники: t=n-2
	* ФОРМУЛА поиска количества треугольников: triangle = n-2 -> n=5 triangle = 3 , n=7 triangle = 5.
	* Входные данные: точки, количество вершин - n
	* В качестве первой точки возьмем первую в списке. Далее по очереди будем брать следующие.
	* Пример:
		n = number_vertex; - количество вершин
		for(i = 1; i<number_vertex++ ; number_vertex++)
			triangle_list(A, i, i+1); 
		т.е. для первого  треугольника 0, 1, 2 номера вершин
			 для второго  треугольника 0, 2, 3
			 для третьего треугольника 0, 3, 4 
			 ....
			if (answer = "The dot is on the border")
			{
				//продолжить проверку
			}

	*/

	// Проверка на совпадение с вершиной
	for (auto &elem : dots)
	{
		if(EqualDot(elem,P)==true)
		{
			return answer = "Dot is equal to this height";
			cout << elem.X() <<'\t' << elem.Y();
			break;
		}
	}

	
	int check_border = 0; 
	Dot startDot = Dot();
	startDot = dots.front(); 
	dots.erase(dots.begin());
	for (int i = 0; i < dots.size() - 1; ++i)
	{
		//Last triangle ADE startDot = 0, dot[3], dot[4] 
		// startDot = 0, A, dots[0] = B, dots[1]= C : i = 0
		// startDot = 0 = A, dots[2] = C, dots[i+1] = D : i = 1
		// startDot = 0 = A , dots[3] = D , dots[i+1] = E : i = 2
		cout << "WORK WITH TRINAGLE" << i;
		answer = Baricenter_method(startDot,dots[i], dots[i+1], P);
		cout << endl << answer << endl;
		//cout << answer<< "COORDINATES: 2"<<dots[i].X() << dots[i].Y() << "COORDINATES: 3" << dots[i+1].X() << dots[i+1].Y;
		if(answer.compare("\nGiven dot in the triangle")==0)
		{
			return answer;
		}
		else
		{
			// if(answer.compare("\nThe dot is on the border")==0)
			// {
			// 	check_border++; //если встретили на границе точку	
			// }
			// if(check_border > 1)
			// {
			// 	return answer;
			// }
			continue;
			
		}
	}
	return answer;
}


int main()
{
	cout << "---------------START--------------------\n";
	cout << "Enter the coordinates for the following dots:\n";
	Dot A = Dot();
	Dot B = Dot();
	Dot C = Dot();
	Dot D = Dot();
	Dot E = Dot();


	Dot P = Dot(); // Точка которую будем проверять

	// Test
	A.setCoordinates(1.0,2.0);
	B.setCoordinates(2.0,4.0);
	C.setCoordinates(4.0,4.0);
	D.setCoordinates(4.0,2.0);
	E.setCoordinates(3.0,1.0);
	
	P.setCoordinates(3.0,1.9);
	//cout << "A \n";
	// A.setCoordinates(A);
	// cout << "B \n";
	// B.setCoordinates(B);
	// cout << "C \n";
	// C.setCoordinates(C);
	// cout << "P \n";
	// P.setCoordinates(P);
	
	vector<Dot> dots;
	dots.push_back(A);	
	dots.push_back(B);
	dots.push_back(C);
	dots.push_back(D);
	dots.push_back(E);
	
	
	

	cout << "-------------Check by Polygon baricentric method----------------------- \n";
	string result = Polygon_method(dots,P);
	cout << result;
	// cout << "-------------Check by triangle method----------------------- \n";
	// string result = Triangle_method(A, B, C, P);
	// cout << "\n";
	// cout << result;

	// cout << "---------------Check by baricentric method---------------------\n";
	// string BarResult = Baricenter_method(A, B, C, P);
	// cout << BarResult;

	return 0;
}