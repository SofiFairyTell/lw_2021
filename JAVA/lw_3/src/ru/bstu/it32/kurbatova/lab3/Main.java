package ru.bstu.it32.kurbatova.lab3;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

/**
 * Написать программу, которая:
 * 1) Считывает с консоли количество фигур (распознавать количество фигур при вводе пользователем таких строк:
 * вап4явап, аа4а555 (в этом случае надо распознать первое число))
 * 2) В цикле считывает параметры. Сначала спрашивается тип фигуры и создается объект нужного класса.
 * Затем у объекта вызывается метод init() и вводятся характеристики объекта. Понятно, что метод init() разный у разных классов.
 * 3) Считанные объекты добавляются в массив
 * 4) Ищется фигура  с наибольшим периметром и выводится на экран (вывод через toString())
 *
 * */
public class Main {
    private static int getNumbers(String s)
    {
        String[] n = s.split(""); //array of strings
        StringBuffer f = new StringBuffer(); // buffer to store numbers
        for (int i = 0; i < n.length; i++)
        {
            if((n[i].matches("[0-9]+")))
            {
                f.append(n[i]); //appending
                return Integer.parseInt(f.toString());
            }
        }
        return 0;
    }
    static int GetMax(ArrayList<Figure.GeometricShapes> shapes,int max)
    {
        for(int i = 1; i< shapes.size();i++)
        {
            if(shapes.get(max).getPerimeter() < shapes.get(i).getPerimeter())
            {
                max = i;
            }
        }
        return max;
    }

    public static void main(String[] args)
    {
        Scanner scan = new Scanner(System.in);
        System.out.println("Введите количество фигур:");
        String str = scan.nextLine();
        int amount = Main.getNumbers(str);
        System.out.println("Фигур будет: " + amount);
        int max = 0; //индекс фигуры с максимальным периметром

        ArrayList<Figure.GeometricShapes> shapes = new ArrayList<>();
        System.out.println("Введите имя фигуры: triangle circle rectangle");
        String shape_name;
        shape_name = scan.next();
        do {
            switch (shape_name)
            {
                case "triangle":
                    for (int i = 0; i<amount;i++)
                    {
                        Triangle triangle = new Triangle();
                        triangle.init(scan);
                        shapes.add(triangle);
                    }
                    max = Main.GetMax(shapes,max);
                    System.out.println(shapes.get(max).toString());
                    shapes.clear();
                    max = 0;
                    break;
                case "circle":
                    for (int i = 0; i<amount;i++)
                    {
                        Circle circle = new Circle();
                        circle.init(scan);
                        shapes.add(circle);
                    }
                    System.out.println(shapes.get(Main.GetMax(shapes,max)).toString());
                    shapes.clear();
                    max = 0;
                    break;
                case "rectangle":
                    for (int i = 0; i<amount;i++)
                    {
                        Rectangle rectangle = new Rectangle();
                        rectangle.init(scan);
                        shapes.add(rectangle);
                    }
                    System.out.println(shapes.get(Main.GetMax(shapes,max)).toString());
                    shapes.clear();
                    max = 0;
                    break;
                default:
                    throw new IllegalStateException("Unexpected value: " + shape_name);
            }
            System.out.println("Введите имя фигуры: triangle circle rectangle");
            shape_name = scan.next();
        }while(!shape_name.equals("no"));
    }
}


