package ru.bstu.it32.kurbatova.lab1;

import java.util.InputMismatchException;
import java.util.Scanner;

//Новый класс для исключений связанных с неправильным вводом
class InputException extends Exception
        {
            public InputException(String message)
            {
                super(message);
            }
        }

public class MenuCommand
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
        }
        catch(InputMismatchException ex)
        {
            System.out.println(ex.getMessage());
        }
    }
    static void MarkTranslationMenu()
    {
        try
        {
            Scanner input = new Scanner(System.in);
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
        }
        catch(InputMismatchException ex)
        {
            System.out.println(ex.getMessage());
        }
    }
}
