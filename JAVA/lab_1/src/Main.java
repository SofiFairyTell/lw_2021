import java.util.*;
import java.math.*;
/*Вариант 10
 Дан круг радиуса R.
 Определить, поместится ли правильны
 треугольник со стороной а в этом круге.*/

class PartOne
{
	static void isTriangleInCircle(double radius, double length)
	{
		double triangle = length*(Math.sqrt(3)/3);
		if(radius >= triangle)
		{
			System.out.print("Поместиться!");
		}
		else
		{
			System.out.print(" Не поместиться!");
		}
	}
}
/*Составить программу, позволяющую получить
словесное описание школьных отметок
(1 — «плохо», 2 — «неудовлетворительно»
3-«удовлетворительно»,  4— «хорошо», 5 — «отлично»).*/

 
 public class Main
{
	public static void main(String[] args)
	{
		Scanner input = new Scanner(System.in);

		System.out.print("Длина стороны треугольника: ");
		double triangleLength = input.nextDouble();

		System.out.print("Введите радиус: ");
		double radius = input.nextDouble();
		PartOne.isTriangleInCircle(radius,triangleLength);
	    
	}
}
