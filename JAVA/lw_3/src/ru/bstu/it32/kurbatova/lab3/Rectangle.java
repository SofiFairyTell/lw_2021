package ru.bstu.it32.kurbatova.lab3;

import java.util.Scanner;

public class Rectangle extends Figure.GeometricShapes {
    private double a,b,c,d;

    public Rectangle() {
        super(4);
    }

    @Override
    public void init(Scanner scanner)
    {
        System.out.println("Введите стороны прямоугольника:");
        a = scanner.nextDouble();
        b = scanner.nextDouble();
        c = scanner.nextDouble();
        d = scanner.nextDouble();
    }
    @Override
    public void init(String string)
    {
        String[] arr = string.split(",");
        a = Double.parseDouble(arr[0]);
        b = Double.parseDouble(arr[1]);
        c = Double.parseDouble(arr[2]);
        d = Double.parseDouble(arr[3]);
    }

    @Override
    public double getPerimeter() {
        return a+b+c+d;
    }
    @Override public String toString()
    {
        return "Parameters [a =" + a + "; " + "b = " + b + "c = " + c + ";" + "d = "+ d + ";"
                +  "( Perimeter=" + this.getPerimeter() + " )]";}
}

