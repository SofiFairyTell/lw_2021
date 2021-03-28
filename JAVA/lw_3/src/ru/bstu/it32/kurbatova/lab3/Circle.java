package ru.bstu.it32.kurbatova.lab3;

import java.util.Scanner;

public class Circle extends Figure.GeometricShapes {
    private double radius;
    public Circle()
    {
        super(0);
    }

    @Override
    public void init(Scanner scanner) {

    }

    @Override
    public double getPerimeter() {
        return radius * 2*Math.PI;
    }
}
