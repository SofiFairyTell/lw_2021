package ru.bstu.it32.kurbatova.lab1;

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.InputMismatchException;
import java.util.Scanner;


public class MenuCommand
{
    static void TriangleInCircleMenu() {
        Scanner input = new Scanner(System.in);
        System.out.print("Консоль (console) или файл (file)?: ");
        String answer = input.next();
        switch (answer) {
            case "console":
                {
                try {
                    System.out.print("Длина стороны треугольника: ");
                    int triangleLength = input.nextInt();
                    System.out.print("Введите радиус: ");
                    int radius = input.nextInt();
                    if (triangleLength <= 0 && radius <= 0) {
                        throw new InputException("Значения длин не могут быть меньше или равны 0");
                    } else {
                        ComputeMethod.isTriangleInCircle(radius, triangleLength);
                    }
                } catch (InputException ex) {
                    System.out.println(ex.getMessage());
                    System.exit(-1);
                } catch (InputMismatchException ex) {
                    System.out.println(ex.getMessage());
                    System.exit(-1);
                }
            }
            break;
            case "file": {
                int arg[] = MenuCommand.FileReader();
                ComputeMethod.isTriangleInCircle(arg[0], arg[1]);
            }
            break;
        }

    }

    static void MarkTranslationMenu() {

        Scanner input = new Scanner(System.in);
        System.out.print("Консоль (console) или файл (file)?: ");
        String answer = input.next();
        switch (answer) {
            case "console": {
                try {
                    System.out.print("Введите оценку:");
                    int mark = input.nextInt();
                    if (mark <= 0) {
                        throw new InputException("Значение не может быть меньше или равны 0");
                    } else {
                        ComputeMethod.markTranslator(mark);
                    }
                } catch (InputException ex) {
                    System.out.println(ex.getMessage());
                    System.exit(-1);
                } catch (InputMismatchException ex) {
                    System.out.println(ex.getMessage());
                    System.exit(-1);
                }
            }
            break;
            case "file": {
                int arg[] = MenuCommand.FileReader();
                ComputeMethod.markTranslator(arg[0]);
            }
            break;
        }
    }

    static void TrigonometryFunctionMenu() {
        Scanner input = new Scanner(System.in);
        System.out.print("Консоль (console) или файл (file)?: ");
        String answer = input.next();
        switch (answer) {
            case "console": {
                try {
                    System.out.print("Введите начало и конец:");
                    int start = input.nextInt();
                    int end = input.nextInt();
                    System.out.print("Введите шаг:");
                    int step = input.nextInt();
                    if (step <= 0) {
                        throw new InputException("Шаг не может быть меньше или равны 0");
                    } else {
                        ComputeMethod.TrigonometryFunction(start, end, step);
                    }
                } catch (InputException ex) {
                    System.out.println(ex.getMessage());
                    System.exit(-1);
                } catch (InputMismatchException ex) {
                    System.out.println(ex.getMessage());
                    System.exit(-1);
                }
            }
            break;
            case "file": {
                int arg[] = MenuCommand.FileReader();
                ComputeMethod.TrigonometryFunction(arg[0], arg[1], arg[2]);
            }
            break;
        }
    }

    static void ArraySumMenu() {
        Scanner input = new Scanner(System.in);
        System.out.print("Консоль (console) или файл (file)?: ");
        String answer = input.next();
        switch (answer) {
            case "console": {
                try {
                    System.out.print("Введите количество элементов массива: ");
                    int size = input.nextInt();
                    int array[] = new int[size];
                    System.out.print("Введите последовательность чисел: ");

                    if (size <= 0) {
                        throw new InputException("Шаг не может быть меньше или равны 0");
                    } else {
                        for (int i = 0; i < size; i++) {
                            array[i] = input.nextInt();
                        }
                        ComputeMethod.ArraySum(array);
                    }
                } catch (InputException ex) {
                    System.out.println(ex.getMessage());
                    System.exit(-1);
                } catch (InputMismatchException ex) {
                    System.out.println(ex.getMessage());
                    System.exit(-1);
                }
            }
            break;
            case "file": {
                int arg[] = MenuCommand.FileReader();
                ComputeMethod.ArraySumWhile(arg);
            }
            break;
        }
    }

    static int[] FileReader() {
        Scanner input = new Scanner(System.in);
        System.out.print("Введите путь: ");
        String path = input.nextLine();
        try {
            File file = new File(path);
            if (!file.exists()) {
                file.createNewFile();
                // добавим информацию в указанный файл
                PrintWriter printWriter = new PrintWriter(file);
                printWriter.println("2 5 1");
                printWriter.close();
            }
            Scanner file_read = new Scanner(file);
            String string = "";
            while (file_read.hasNextLine()) {
                string = file_read.nextLine();
            }
            String[] intString = string.split(" ");
            int numbers[] = new int[intString.length];
            for (int i = 0; i < intString.length; i++) {
                numbers[i] = Integer.parseInt(intString[i]);
            }
            return numbers;
        } catch (IOException ex) {
            ex.printStackTrace();
            return new int[0];
        }
    }
}
