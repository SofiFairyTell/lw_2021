package ru.bstu.it32.kurbatova.lab3;

import java.util.Scanner;


public class Figure {



    public static interface Shape
    {
        public double getArea();
        public  double init();
    }

    public  static  abstract  class GeometricShapes
    {
        private static int sides; // количество сторон

        public GeometricShapes(int side)
        {
            sides = side;
            Scanner number = new Scanner(System.in);

        }

        public int getSides()
        {
            return sides;
        }
        public abstract void init(Scanner scanner);	// считывание параметров с консоли
        public abstract void init(String string);	// считывание параметров с консоли
        public abstract double getPerimeter();	// возвращает  периметр
    }
    //Общие поля


    public String toString()        // возвращается состояние объекта в виде строки
    {
        return null;
    }


}


