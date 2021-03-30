package ru.bstu.it32.kurbatova.lab3;

import java.util.Scanner;

public class Rectangle extends Figure.GeometricShapes {
    private double a,b;

    public Rectangle() {
        super(4);
    }

    @Override
    public void init(Scanner scanner)
    {
        System.out.println("Введите стороны прямоугольника:");
        a = scanner.nextDouble();
        b = scanner.nextDouble();

    }
    @Override
    public void init(String string)
    {
        String[] arr = string.split(",");
        a = Double.parseDouble(arr[0]);
        b = Double.parseDouble(arr[1]);

    }

    @Override
    public double getPerimeter() {
        return (a+b)*2;
    }
    @Override public String toString()
    {
        return "Parameters RECTANGLE [a =" + a + "; " + "b = " + b+ ";" + super.toString()+"]";}


    @Override
    public int compare(Figure.GeometricShapes o1, Figure.GeometricShapes o2) {
        if (o1.getPerimeter()>o2.getPerimeter())
        {
            return 1;
        }
        else
        if (o1.getPerimeter()<o2.getPerimeter())
        {
            return  -1;
        }
        else
            return 0;
    }
}

