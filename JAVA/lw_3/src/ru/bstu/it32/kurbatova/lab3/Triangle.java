package ru.bstu.it32.kurbatova.lab3;

import java.util.Scanner;

public class Triangle extends Figure.GeometricShapes{

        private double a,b,c;

        public Triangle()
        {
            super(3);
        }
        @Override
        public double getPerimeter()
        {
            return a+b+c;
        }


        @Override
        public void init(Scanner scanner) {

        }
    @Override public String toString()
    {
        return "Cone [a=" + a + "; " + "b=" +
                b + "c=" + ";" + " ( perimeter=" + this.getPerimeter() + " )]";
    }

}
