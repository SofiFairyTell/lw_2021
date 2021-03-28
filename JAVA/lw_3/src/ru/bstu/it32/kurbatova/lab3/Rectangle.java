package ru.bstu.it32.kurbatova.lab3;

import java.util.Scanner;

public class Rectangle extends Figure.GeometricShapes {
    private double a,b,c,d;

    public Rectangle() {
        super(4);
    }


    @Override
    public void init(Scanner scanner) {

    }

    @Override
    public double getPerimeter() {
        return a+b+c+d;
    }
}
