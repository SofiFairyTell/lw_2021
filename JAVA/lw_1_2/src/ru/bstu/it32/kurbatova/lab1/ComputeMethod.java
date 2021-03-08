package ru.bstu.it32.kurbatova.lab1;

import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;
import org.w3c.dom.events.EventException;

import java.util.concurrent.atomic.AtomicInteger;
import java.util.logging.Level;
/**
 * <p>Описание класса ComputeMethod</p>
 * Содержит методы длярешения задач:
 * <ul>
 *     <li>из школьной геометрии</li>
 *     <li>перевода оценок в словесное описание</li>
 * </ul>*/
public class ComputeMethod
{
    /**
     <p> Описание метода "isTriangleInCircle"</p>
     * Определяет поместиться ли правильный треугольник в круге
     * @param radius Радиус круга для размещения
     * @param length Длина стороны треугольника
     * @return answer Ответ в виде строки
    */
    @NotNull
    @Contract(pure = true)
    public static String isTriangleInCircle(int radius, int length)
    {
        String result;
        double triangle = length*(Math.sqrt(3)/3);
        if(radius >= triangle) return "Поместится!\n";
        else return "Не поместится!\n";
    }
    /**
     * <p>Описание метода "markTranslator"</p>
     * Позволяет получить словесное описание школьных отметок
     * 1 — «плохо», 2 — «неудовлетворительно», 3-«удовлетворительно»,  4— «хорошо», 5 — «отлично»
     * @param mark Школьная отметка
     * @return translate Словесное описание школьных отметок
     */
   @NotNull
   @Contract(pure = true)
   public static String markTranslator(int mark)
    {
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
    /**
     * <p>Описание метода "TrigonometryFunction"</p>
     * Строит промежуточные точки между началом линии и ее концом с определенным шагом
     * @param start Начальная точка
     * @param end Конечная точка
     * @param step Шаг
     * @return array Массив значений в видет аргумент - значение функции
     */
    public static double[][] TrigonometryFunction(int start, int end, int step)
    {
        int rows = (int) ((end - start) / step) + 1;
        double[][] array;
        array = new double[rows][2];
        try {
                for (int i = 0; i < rows; i++)
                {
                    double y = Math.sin(start) + 0.5 * Math.cos(start);
                    array[i][0] = start;
                    array[i][1] = y;
                    start += step;
                }
                return array;
        }catch (EventException e){
            Main.logger.log(Level.SEVERE, "Проблема с созданием массива: " + e.getMessage());
            return null;
        }
    }
    /**
     * <p>Описание метода "ArraySum"</p>
     * Вычисляет сумму элементов массива между максимальным и минимальным элементом.
     * Механизм поиска реализован с использованием в цикле for
     * @param array массив элементов
     * @return sum сумма между максимальным и минимальным элементом
     */
   public static String ArraySum(int[] array)
   {
        int min = 0, max = 0;
        for (int i = 0; i < array.length; ++i)
        {
            if (array[i] < array[min])
                min = i;
            if (array[i] > array[max])
                max = i;
        }
        int left = (min >= max) ? max : min;
        int right = (min < max) ? max : min;
        AtomicInteger Sum = new AtomicInteger();
        for (int i = left; i <= right; i++)
           Sum.addAndGet(array[i]);
        Main.logger.log(Level.INFO, "Сумма вычислена");
        return Integer.toString(Sum.get());
    }
    /**
     * <p>Описание метода "ArraySumWhile"</p>
     * Вычисляет сумму элементов массива между максимальным и минимальным элементом.
     * Механизм поиска реализован с использованием в цикле while
     * @param array массив элементов
     * @return sum сумма между максимальным и минимальным элементом
     */

   public static String ArraySumWhile(int[] array)
   {
        int min = 0, max = 0, i = 0;
        System.out.print("Метод с циклом While");
        while (i < array.length)
        {
            if (array[i] < array[min])
                min = i;
            if (array[i] > array[max])
                max = i;
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
