#include <iostream>
#include<cmath>


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
		dot.setX(value1); dot.setY(value2);
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

string Triangle_method(Dot& A, Dot& B, Dot& C, Dot& P )
{
	string answer;
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
	if (EqualDot(P,B) == true || EqualDot(P,A) = true || EqualDot(P,C))
	{
		cout<<"Точка совпала с одной из вершин"<<endl;
	}
	else
	{
		//координаты векторов
		// Может не точки?? 
		Dot vector_pa = Dot();
		Dot vector_pb = Dot();
		Dot vector_pc = Dot();

		vector_pa.setCoordinates(P.X() - A.X(), P.Y() -A.Y());
		vector_pb.setCoordinates(P.X() - B.X(), P.Y() - B.Y());
		vector_pc.setCoordinates(P.X() - C.X(), P.Y() - C.Y());
	
		// векторы длины
		float pa = sqrt(pow((P.X() - A.X()),2)+pow(P.Y() - A.Y(),2));
		float pb = sqrt(pow((P.X() - B.X()),2)+pow(P.Y() - B.Y(),2));
		float pc = sqrt(pow((P.X() - C.X()),2)+pow(P.Y() - C.Y(),2));
		// углы
		float angle_apb = (acos((vector_pa.X()*vector_pb.X()+vector_pa.Y()*vector_pb.Y())/(pa*pb)) *180)/ PI ; //в градусах
		float angle_bpc = (acos((vector_pb.X()*vector_pc.X()+vector_pb.Y()*vector_pc.Y())/(pb*pc)) *180)/ PI ; //в градусах
		float angle_apc = (acos((vector_pa.X()*vector_pc.X()+vector_pa.Y()*vector_pc.Y())/(pa*pc)) *180)/ PI ; //в градусах
		// сумма углов
		float sum_angle = angle_apb + angle_bpc + angle_apc;
		if (sum_angle != 360)
		{
			cout << "Точка вне обозначенной области"
		}
		else 
			cout << "Точка внутри обозначенной области"

	}

};
string Baricenter_menthod()
{
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