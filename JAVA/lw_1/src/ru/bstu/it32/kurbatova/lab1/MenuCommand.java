package ru.bstu.it32.kurbatova.lab1;

import java.util.InputMismatchException;
import java.util.Scanner;



class MenuCommand
{
    static void TriangleInCircleMenu()
    {
        Scanner input = new Scanner(System.in);
        try
        {
            System.out.print("Длина стороны треугольника: ");
            double triangleLength = input.nextDouble();
            System.out.print("Введите радиус: ");
            double radius = input.nextDouble();
            if(triangleLength <=0 && radius <=0)
            {
                throw new InputException("Значения длин не могут быть меньше или равны 0");
            }
            else
            {
                ComputeMethod.isTriangleInCircle(radius,triangleLength);
            }
        }
        catch (InputException ex)
        {
            System.out.println(ex.getMessage());
            System.exit(-1);
        }
        catch(InputMismatchException ex)
        {
            System.out.println(ex.getMessage());
            System.exit(-1);
        }
    }
    static void MarkTranslationMenu()
    {
        Scanner input = new Scanner(System.in);
        try
        {
            System.out.print("Введите оценку:");
            int mark= input.nextInt();
            if( mark <=0 )
            {
                throw new InputException("Значение не может быть меньше или равны 0");
            }
            else
            {
                ComputeMethod.markTranslator(mark);
            }
        }
        catch (InputException ex)
        {
            System.out.println(ex.getMessage());
            System.exit(-1);
        }
        catch(InputMismatchException ex)
        {
            System.out.println(ex.getMessage());
            System.exit(-1);
        }
    }

}
