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
//            else {
//                //parsing to int and returning value
//                return Integer.parseInt(f.toString());
//            }
        }
        return 0;
    }


    public static void main(String[] args)
    {
        Scanner scan = new Scanner(System.in);
        System.out.println("Введите количество фигур:");
        String str = scan.nextLine();
        int amount = Main.getNumbers(str);
        System.out.println("Фигур будет: " + amount);
        String shape;

        System.out.println("Введите имя фигуры: triangle circle rectangle");
        shape = scan.next();
        do {
            switch (shape)
                {
                    case "triangle":
                        Triangle triangle = new Triangle();
                        ArrayList<Figure.GeometricShapes> shapes = new ArrayList<Figure.GeometricShapes>();
                        for (int i = 0; i<amount;i++)
                        {
                            triangle.init(scan);

                            shapes.add(i,triangle);
                            //triangle.getSides();
                            //assert shapes != null;
                        }
                        break;
                    case "circle":
                        break;
                    case "rectangle":
                        break;
                }
            System.out.println("Введите имя фигуры: triangle circle rectangle");
            shape = scan.next();
        }while(!shape.equals("no"));
    }

}

