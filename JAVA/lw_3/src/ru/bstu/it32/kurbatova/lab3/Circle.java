package ru.bstu.it32.kurbatova.lab3;

import java.util.Scanner;

public class Circle extends Figure.GeometricShapes
{
    private double radius;

    public Circle() {
        super(0);
    }

    @Override
    public void init(Scanner scanner)
    {
        System.out.println("Введите радиус круга:");
        try {
            radius = scanner.nextDouble();
            if (radius<=0)
            {
                throw new InputException("Радиус не может быть меньше или равен 0");
            }
        }catch (Exception ex)
        {
            System.out.println(ex.getMessage());
        }
    }

    @Override
    public double getPerimeter()
    {  return radius * 2*Math.PI;  }

    @Override public String toString()
    {    return "Parameters [radius=" + radius + "; "  + " ( Perimeter=" + this.getPerimeter() + " )]";
    }
}

