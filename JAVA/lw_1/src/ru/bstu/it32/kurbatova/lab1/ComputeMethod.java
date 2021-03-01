package ru.bstu.it32.kurbatova.lab1;

import javax.lang.model.type.NullType;

public class ComputeMethod
{

    public static String isTriangleInCircle(int radius, int length)
    {
        /**
            <p> Описание метода "Треугольник в Окружности"</p>
         * Определяет поместиться ли правильный треугольник в круге
         * @param radius Радиус круга для размещения
         * @param length Длина стороны треугольника
         * @return answer Ответ в виде строки
         */
        String result;
        double triangle = length*(Math.sqrt(3)/3);
        if(radius >= triangle) return "Поместиться!\n";
        else return "Не поместиться!\n";
    }

   public static String markTranslator(int mark)
    {
        /**
         * <p>Описание метода "Перевод оценок"</p>
         * Позволяет получить словесное описание школьных отметок
         * 1 — «плохо», 2 — «неудовлетворительно», 3-«удовлетворительно»,  4— «хорошо», 5 — «отлично»
         * @param mark Школьная отметка
         * @return translate Словесное описание школьных отметок
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

    public static double[][] TrigonometryFunction(int start, int end, int step)
    {
        /**
         * <p>Описание метода "Тригонометрическая функция"</p>
         * Строит промежуточные точки между началом линии и ее концом с определенным шагом
         * @param start Начальная точка
         * @param end Конечная точка
         * @param step Шаг
         * @return array Массив значений в видет аргумент - значение функции
         */
        int rows = (int) ((end - start) / step) + 1;
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

   public static String ArraySum(int[] array) {
       /**
        * <p>Описание метода "Сумма массива"</p>
        * Вычислияет сумму элементов массива между максимальным и минимальным элементом
        * @param array массив элементов
        * @return sum сумма между максимальным и минимальным элементом
        */
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
        int Sum = 0;
        for (int i = left; i <= right; i++) {
            Sum += array[i];
        }
        return Integer.toString(Sum);
    }

   public static String ArraySumWhile(int[] array) {
       /**
        * <p>Описание метода "Сумма массива"</p>
        * Вычислияет сумму элементов массива между максимальным и минимальным элементом
        * @param array массив элементов
        * @return sum сумма между максимальным и минимальным элементом
        */
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
        int Sum;
        Sum = 0;
        for (int j = left; j <= right; j++)
            Sum += array[j];
        return Integer.toString(Sum);
    }
}
