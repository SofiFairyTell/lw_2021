package ru.bstu.it32.kurbatova.lab1;

import java.util.*;

public class Main
{
    public static void main(String[] args)
    {
        String command;
        Scanner input = new Scanner(System.in);
        do {
            System.out.print("Введите команду: ");
            command = input.next();
            switch(command)
            {
                case "first":
                    MenuCommand.TriangleInCircleMenu();
                    break;
                case "second":
                    MenuCommand.MarkTranslationMenu();
                    break;
                case "tree":
                    ComputeMethod.TrigonometryFunction(0.0,6.0,2.0);
                    break;
            }
        }while(command.equals("далее"));
    }
}
