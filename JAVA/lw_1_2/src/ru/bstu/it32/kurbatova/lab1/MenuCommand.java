package ru.bstu.it32.kurbatova.lab1;

import java.io.*;
import java.text.MessageFormat;
import java.util.InputMismatchException;
import java.util.Scanner;
import java.util.logging.Level;

/**
 * <p>Описание класса MenuCommand</p>
 * Описаны методы управления программой. */
public class MenuCommand {
    static void TriangleInCircleMenu() {
        Scanner input = new Scanner(System.in);
        System.out.print("Консоль (console) или файл (file)?: ");
        String answer = input.next();
        switch (answer) {
            case "console": {
                try {
                        System.out.print("Длина стороны треугольника: ");
                        int triangleLength = input.nextInt();
                        System.out.print("Введите радиус: ");
                        int radius = input.nextInt();
                        if (triangleLength <= 0 && radius <= 0) {
                            throw new InputException("Значения длин не могут быть меньше или равны 0");
                        } else {
                            String varLogger = MessageFormat.format("Введены: радиус = {0}, длина стороны = {1}", radius, triangleLength);
                            Main.logger.log(Level.FINE, varLogger);
                            System.out.print(ComputeMethod.isTriangleInCircle(radius, triangleLength));
                        }
                } catch (InputException ex)
                {
                    Main.logger.log(Level.SEVERE,"Ошибка в методе треугольников",ex);
                    System.out.println(ex.getMessage());
                    System.exit(-1);
                } catch (InputMismatchException ex)
                {
                    System.out.println(ex.getMessage());
                    System.exit(-1);
                }
            }
            break;
            case "file": {
                int arg[] = MenuCommand.FileReader();
                System.out.println(ComputeMethod.isTriangleInCircle(arg[0], arg[1]));
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
                        System.out.println(ComputeMethod.markTranslator(mark));
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
                System.out.println(ComputeMethod.markTranslator(arg[0]));
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
                    if (step <= 0 || step > end) {
                        String varLogger = MessageFormat.format("Введены: шаг = {0}, конечная точка = {1}. " +
                                "Шаг не может быть меньше или равен 0 или больше конечной точки", step, end);
                        Main.logger.log(Level.SEVERE, varLogger);
                        throw new InputException("Шаг не может быть меньше или равны 0 или больше конечной точки");
                    } else {
                        double[][] array = ComputeMethod.TrigonometryFunction(start, end, step);
                        TableView(array);
                    }
                } catch (InputException ex) {
                    Main.logger.log(Level.SEVERE, ex.getMessage());
                    //System.out.println(ex.getMessage());
                    System.exit(-1);
                } catch (InputMismatchException ex) {
                    Main.logger.log(Level.SEVERE, ex.getMessage());
                    System.exit(-1);
                }
            }
            break;
            case "file": {
                int arg[] = MenuCommand.FileReader();
                double[][] array = ComputeMethod.TrigonometryFunction(arg[0], arg[1], arg[2]);
                TableView(array);
            }
            break;
        }
    }

    static void TableView(double[][] array) {
        //вывод в табличном виде
        System.out.printf("%-10s%-25s%n", "Аргумент", "Значение");
        System.out.println("-----------------------------------------------------");
        for (int i = 0; i < array.length; i++) {
            System.out.printf("%-10.2f%-27.2f%n", array[i][0], array[i][1]);
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
                        Main.logger.log(Level.SEVERE, "Шаг не может быть меньше или равны 0");
                        throw new InputException("Шаг не может быть меньше или равны 0");

                    } else {
                        for (int i = 0; i < size; i++) {
                            array[i] = input.nextInt();
                        }
                        System.out.printf("Сумма между максимальным и минимальным элементов %s\n", ComputeMethod.ArraySum(array));
                    }
                } catch (InputException ex) {
                    Main.logger.log(Level.SEVERE, ex.getMessage());
                    System.out.println(ex.getMessage());
                    System.exit(-1);
                } catch (InputMismatchException ex) {
                    Main.logger.log(Level.SEVERE, ex.getMessage());
                    System.out.println(ex.getMessage());
                    System.exit(-1);
                }
            }
            break;
            case "file": {
                int arg[] = MenuCommand.FileReader();
                System.out.printf("Сумма между максимальным и минимальным элементов %s\n", ComputeMethod.ArraySumWhile(arg));
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
                try {
                    boolean created = file.createNewFile();
                    if (created) {
                        System.out.println("Файл создан!");
                        // добавим информацию в указанный файл
                        PrintWriter printWriter = new PrintWriter(file);
                        printWriter.println("2 5 1");
                        printWriter.close();
                        /*Выведем содержимое файла*/
                        try (FileReader fin = new FileReader(file)) {
                            BufferedReader reader = new BufferedReader(fin);
                            String line = reader.readLine();
                            while (line != null) {
                                System.out.println(line);
                                line = reader.readLine();
                            }
                        } catch (FileNotFoundException e) {
                            Main.logger.log(Level.WARNING, "Файл не найден: " + e.getMessage());
                            e.printStackTrace();
                        } catch (IOException e) {
                            Main.logger.log(Level.SEVERE, e.getMessage());
                            e.printStackTrace();
                        }
                    }
                } catch (IOException ex) {
                    System.out.println(ex.getMessage());
                }

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

    static void FileOpen()
    {
        Scanner input = new Scanner(System.in);
        System.out.print("Введите путь: ");
        String path = input.nextLine();
        File file = new File(path);
        /*Выведем содержимое файла*/
        try (FileReader fin = new FileReader(file)) {
            BufferedReader reader = new BufferedReader(fin);
            String line = reader.readLine();
            while (line != null) {
                System.out.println(line);
                line = reader.readLine();
            }
        } catch (FileNotFoundException e) {
            Main.logger.log(Level.WARNING, "Файл не найден:" + path, e);
            e.printStackTrace();
        } catch (IOException e) {
            Main.logger.log(Level.SEVERE, e.getMessage());
            e.printStackTrace();
        }
    }
}
