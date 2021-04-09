package ru.bstu.it32.kurbatova.lab3;

import java.util.Scanner;

public class Circle extends Figure.GeometricShapes
{
    private double radius;
    private String name;
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
    public void init(String string)
    {
        String[] arr = string.split(",");
        radius = Double.parseDouble(arr[0]);
        name = arr[1];
    }
    @Override
    public double getPerimeter()
    {  return radius * 2*Math.PI;  }

    @Override public String toString()
    {    return "Parameters CIRCLE [radius = " + radius + "; "  + super.toString();
    }


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

