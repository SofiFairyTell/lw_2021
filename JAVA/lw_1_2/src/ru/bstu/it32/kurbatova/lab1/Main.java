package ru.bstu.it32.kurbatova.lab1;

import java.util.*;
import java.util.logging.Logger;

public class Main
{
    public static Logger logger = LoggerClass.setLog("logger_Error");
    /**<p>Описание команд управления</p>
     * Для управленияп программной предусмотрены такие команды:
     *<ul>
     * <li>first    -   для запуска функции TriangleInCircle</li>
     * <li>second   -   для запуска функции MarkTranslator </li>
     * <li>tree     -   для запуска функции TrigonometryFunction </li>
     * <li>four     -   для запуска функции ArraySum</li>
     * <li>end      -   для завершения работы с программой</li>
     * </ul> */
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
                case "open":
                    MenuCommand.FileOpen();
                    break;
            }
            System.out.print("Введите команду: ");
            command = input.next();
        }while(!command.equals("end"));
    }
}
