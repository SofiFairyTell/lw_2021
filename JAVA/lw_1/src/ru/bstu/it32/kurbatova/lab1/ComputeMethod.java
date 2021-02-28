package ru.bstu.it32.kurbatova.lab1;

import javax.lang.model.type.NullType;

public class ComputeMethod
{
    static String isTriangleInCircle(int radius, int length)
    {
        /**
         * Определяет поместиться ли правильный треугольник в круге
         * @param radius Радиус круга для размещения
         * @param length Длина стороны треугольника
         */
            String result;
            double triangle = length*(Math.sqrt(3)/3);
            if(radius >= triangle)
            {
                return "Поместиться!\n";
            }
            else
            {
                return "Не поместиться!\n";
            }
    }
    static String markTranslator(int mark)
    {
        /**
         * Позволяет получить словесное описание школьных отметок
         * 1 — «плохо», 2 — «неудовлетворительно», 3-«удовлетворительно»,  4— «хорошо», 5 — «отлично»
         * @param mark Школьная отметка
         */
        String result;
        switch(mark)
        {
            case 1:
                return "'Плохо'\n";
            case 2:
                return "'Неудовлетворительно'\n";
            case 3:
                return  "'Удовлетворительно'\n";
            case 4:
                return  "'Хорошо'\n";
            case 5:
                return  "'Отлично'\n";
            default:
                return "'Данных для такой оценки нет'\n";
        }
    }
    static double[][] TrigonometryFunction(int start, int end, int step)
    {

        int rows = (int) ((end - start) / step) + 1;
        //массив из двух столбцов: 0- значение аргумента, 1 - значение функции
        //вывод в табличном виде
        double[][] array = new double[rows][2];
        for (int i = 0; i < rows; i++)
            {
                double y = Math.sin(start) + 0.5 * Math.cos(start);
                array[i][0] = start;
                array[i][1] = y;
                start += step;
            }
        return array;
    }
    static String ArraySum(int[] array)
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
        return Integer.toString(Summ);
    }

    static String ArraySumWhile(int[] array)
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
        return Integer.toString(Summ);
    }
}
