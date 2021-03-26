
/* <p> Triangle Summ Metthod </p>
	Точка P - ее местоположение нужно определить: внутри, снаружи, на границе
	A, B,C - координаты вершин
	Формула: a*b = |a||b| cos y ,
	где a и b - векторы , y - угол между ними
	Вектора: AB, BC, CA - для треугольника
		|AB| = sqrt((B.x - A.x)^2 + (B.y - A.y)^2 )
	Вычисление:
		cos α = 	(a·b)/ |a|·|b| ~ 0,1 or 0,96 -> arcos a ~ 30`
	у нас для angle APC вектор a = P.x - A.x
		Пример расчета: APB =arcos( (-0.4*0.6 + 4.3*-1.6) / (1.71 * 4.32 ) )= arcos((-7.12 / 7.37)) = 165*93`
	Условия завершения:
	Сумма углов:
		= 360 - точка внутри и на границе
		!= 360 - вне треугольника
	Углы:
		= 180 - точка на границе
	Совпадение координат
		Если P.x = A.x и P.y = A.y, то P - совпадает с A,
		answer = границе треугольника
*/
/* <p>Baricentric coordinates Metthod </p>
	P = aA + b + cC where  (a,b,c) - барицентрические координаты
	P.y = aA + bB + cC where  (a,b,c) - барицентрические координаты
	(a+b+c=1) and a >=0 and b >=0 and c >=0 (*)
	Выходные данные:
		Если * верно и хотя бы одна координат (a, b,c) = 0, то на границе
		Если * верно и хотя бы одна координат (a, b,c) = 1, то совпадение с вершиной
		Если * не верно, то вне треугольника
	denominate = (By - Cy)(Ax - Cx) + (Cx - Bx)(Ay - Cy)
	a = (By - Cy)(Px-Cx) + (Cx-Bx)(Py-Cy) / denominate;
	b = (Cy - Ay)(Px - Cx) + (Ax - Cx)(Py - Cy)/ denominate;
	c = (Ay - By)(Px - Ax) + (Bx -  Ax)(Py - Ay)/ denominate;

*/
/** <p> Divide on Polygon Method </p>
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

			Last triangle ADE startDot = 0, dot[3], dot[4]
			startDot = 0, A, dots[0] = B, dots[1]= C : i = 0
			startDot = 0 = A, dots[2] = C, dots[i+1] = D : i = 1
			startDot = 0 = A , dots[3] = D , dots[i+1] = E : i = 2
	*/
//If we need check how many triangle we can make
//int n = 0;
	//int  triangle = n - 2;
	//do
	//{
	//	cout << "Enter the number of vertex:\n";
	//	cin >> n;
	//} while (n < 2);

	//for (int i = 0; i < n; i++)
	//{
	//	cout << "Enter the X and Y:\n";
	//	cin >> x >> y;
	//	PointF point(x, y);
	//	points.push_back(point);
	//}


/* //Формула для расчета координат середины отрезка: 
	 XcenterP = (C.X() + A.X())/2
	 YcenterP = (C.Y() + A.Y())/2

	 TASK: Найти такие координаты точки P, чтобы проверить ее на check_border == 2

	float XcenterP = (C.X + A.X) / 2;
	float YcenterP = (C.Y + A.Y) / 2;
*/

/*
 //Example of using  class Dot
	
	A.setCoordinates(1.0,2.0);
	B.setCoordinates(2.0,4.0);
	C.setCoordinates(4.0,4.0);
	D.setCoordinates(4.0,2.0);
	E.setCoordinates(3.0,1.0);

	vector<Dot> dots;
	dots.push_back(A);
	dots.push_back(B);
	dots.push_back(C);
	dots.push_back(D);
	dots.push_back(E);
*/

//Old versions of check
// cout << "-------------Check by triangle method----------------------- \n";
// string result = Triangle_method(A, B, C, P);
// cout << "\n";
// cout << result;

// cout << "---------------Check by baricentric method---------------------\n";
// string BarResult = Baricenter_method(A, B, C, P);
// cout << BarResult;