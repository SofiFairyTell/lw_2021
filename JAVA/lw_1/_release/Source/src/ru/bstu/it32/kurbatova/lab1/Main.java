package ru.bstu.it32.kurbatova.lab1;

import java.util.*;

public class Main
{
    public static void main(String[] args)
    {
        String command;
        Scanner input = new Scanner(System.in);
        System.out.print("Введите команду: ");
        command = input.next();
        do{
            switch(command)
            {
                case "first":
                    MenuCommand.TriangleInCircleMenu();
                    break;
                case "second":
                    MenuCommand.MarkTranslationMenu();
                    break;
                case "tree":
                    MenuCommand.TrigonometryFunctionMenu();
                    break;
                case "four":
                    MenuCommand.ArraySumMenu();
                    break;
            }
            System.out.print("Введите команду: ");
            command = input.next();
        }while(!command.equals("end"));
    }
}
