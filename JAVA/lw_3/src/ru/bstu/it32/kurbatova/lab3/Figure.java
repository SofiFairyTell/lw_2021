package ru.bstu.it32.kurbatova.lab3;

import java.util.Comparator;
import java.util.Scanner;

/**
 * to do
 * perimeters - общий
 * конкатенировать
 * super.ToString()
 * количество фигур это max в листе разных*/
public class Figure {

    public static interface Shape
    {
        public double getArea();
        public  double init();
    }

    public  static  abstract  class GeometricShapes implements Comparator<GeometricShapes> {
        private static int sides; // количество сторон
        private static String name;

        public GeometricShapes(int side) {
            sides = side;
        }

        public GeometricShapes(String name) {
            this.name = name;
        }

        public int getSides() {
            return sides;
        }

        public abstract void init(Scanner scanner);    // считывание параметров с консоли

        public abstract void init(String string);    // считывание параметров с консоли

        public abstract double getPerimeter();    // возвращает  периметр

        @Override
        public String toString() {
            return "( Perimeter =" + this.getPerimeter() + ")";
        }

    }


    public String toString()        // возвращается состояние объекта в виде строки
    {
        return null;
    }


}


