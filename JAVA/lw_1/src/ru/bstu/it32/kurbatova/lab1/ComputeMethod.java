package ru.bstu.it32.kurbatova.lab1;

import javax.lang.model.type.NullType;

public class ComputeMethod
{
    static void isTriangleInCircle(int radius, int length)
    {
        /**
         * Определяет поместиться ли правильный треугольник в круге
         * @param radius Радиус круга для размещения
         * @param length Длина стороны треугольника
         */
            double triangle = length*(Math.sqrt(3)/3);
            if(radius >= triangle)
            {
                System.out.print("Поместиться!\n");
            }
            else
            {
                System.out.print(" Не поместиться!\n");
            }
    }
    static void markTranslator(int mark)
    {
        /**
         * Позволяет получить словесное описание школьных отметок
         * 1 — «плохо», 2 — «неудовлетворительно», 3-«удовлетворительно»,  4— «хорошо», 5 — «отлично»
         * @param mark Школьная отметка
         */
        switch(mark) {
            case 1:
                System.out.println("'Плохо'");
                break;
            case 2:
                System.out.println("'Неудовлетворительно'\n");
                break;
            case 3:
                System.out.println("'Удовлетворительно'\n");
                break;
            case 4:
                System.out.println("'Хорошо'\n");
                break;
            case 5:
                System.out.println("'Отлично'\n");
                break;
            default:
                System.out.println("'Данных для такой оценки нет'\n");
        }
    }
    static void TrigonometryFunction(int start, int end, int step)
    {

        int rows = (int) ((end - start) / step);
        //массив из двух столбцов: 0- значение аргумента, 1 - значение функции
        double[][] array = new double[rows][2];
        int x = start;

        do {
            for (int i = 0; i < rows; ++i)
            {
                double y = Math.sin(x) + 0.5 * Math.cos(x);
                array[i][0] = x;
                array[i][1] = y;
                x+=step;
            }
        }while(x<end);
        //вывод в табличном виде
        System.out.printf("%-10s%-25s%n","Аргумент","Значение");
        System.out.println("-----------------------------------------------------");
        for (int i = 0; i < array.length; i++)
        {
            System.out.printf("%-10.2f%-27.2f%n", array[i][0], array[i][1]);
        }
    }
    static void ArraySum(int[] array)
    {
        //int[] array = {2, 1, -1, -2, 0};
        int min = 0, max = 0;

        for (int i = 0; i < array.length; ++i)
        {
            if (array[i] < array[min])
            {
                min = i;
            }
            if (array[i] > array[max])
            {
                max = i;
            }
        }
        int left = (min < max) ? min : max;
        int right = (min < max) ? max : min;
        int Summ = 0;
        for (int i = left; i <= right; i++)
        {
            Summ = Summ + array[i];
        }
        System.out.printf("Сумма между максимальным и минимальным элементов %d\n", Summ);
    }

    static void ArraySumWhile(int[] array)
    {
        int min = 0, max = 0;
        int i = 0;
        System.out.print("Метод с циклом While");
        while (i<array.length)
        {
            if (array[i] < array[min])
            {
                min = i;
            }
            if (array[i] > array[max])
            {
                max = i;
            }
            i++;
        }
        int left = (min < max) ? min : max;
        int right = (min < max) ? max : min;
        int Summ = 0;
        for (int j = left; j <= right; j++)
        {
            Summ = Summ + array[j];
        }
        System.out.printf("Сумма между максимальным и минимальным элементов %d\n", Summ);
    }
}
