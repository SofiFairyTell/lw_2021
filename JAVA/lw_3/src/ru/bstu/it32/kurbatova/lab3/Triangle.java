package ru.bstu.it32.kurbatova.lab3;

import java.util.Scanner;

public class Triangle extends Figure.GeometricShapes{
    static int getNumbers(String s) {

        String[] n = s.split(""); //array of strings
        StringBuffer f = new StringBuffer(); // buffer to store numbers

        for (int i = 0; i < n.length; i++)
        {
            if((n[i].matches("[0-9]+")))
            {// validating numbers
                f.append(n[i]); //appending
                return Integer.parseInt(f.toString());
            }
        }
        return 0;
    }



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
        public void init(Scanner scanner)
        {
            System.out.println("Введите стороны треугольника:");
            a = scanner.nextDouble();
            b = scanner.nextDouble();
            c = scanner.nextDouble();
        }

    @Override public String toString()
    {
        return "Cone [a=" + a + "; " + "b=" +
                b + "c=" + c + ";" + " ( perimeter=" + this.getPerimeter() + " )]";
    }

}