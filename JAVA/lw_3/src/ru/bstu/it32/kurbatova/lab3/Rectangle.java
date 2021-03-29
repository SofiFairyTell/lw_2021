package ru.bstu.it32.kurbatova.lab3;

import java.util.Scanner;

public class Rectangle extends Figure.GeometricShapes {
    private double a,b,c,d;

    public Rectangle(int side) {
        super(side);
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
    public double getPerimeter() {
        return a+b+c+d;
    }
    @Override public String toString()
    {
        return "Parameters [a =" + a + "; " + "b = " + b + "c = " + c + ";" + "d = "+ d + ";"
                +  "( Perimeter=" + this.getPerimeter() + " )]";}
}

