package ru.bstu.it32.kurbatova.lab1;

class ComputeMethod
{
    static void isTriangleInCircle(double radius, double length)
    {
        /**
         * Определяет поместиться ли правильный треугольник в круге
         * @param radius Радиус круга для размещения
         * @param length Длина стороны треугольника
         */
            double triangle = length*(Math.sqrt(3)/3);
            if(radius >= triangle)
            {
                System.out.print("Поместиться!");
            }
            else
            {
                System.out.print(" Не поместиться!");
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
                System.out.println("'Неудовлетворительно'");
                break;
            case 3:
                System.out.println("'Удовлетворительно'");
                break;
            case 4:
                System.out.println("'Хорошо'");
                break;
            case 5:
                System.out.println("'Отлично'");
                break;
            default:
                System.out.println("'Данных для такой оценки нет");
        }
    }
    static void TrigonometryFunction(double start, double end, double step)
    {

        int rows = (int) ((end - start) / step);
        //массив из двух столбцов: 0- значение аргумента, 1 - значение функции
        double[][] array = new double[rows][2];
        double x = start;
        while(x<end)
        {
            for (int i = 0; i < rows; ++i)
            {
                double y = Math.sin(x) + 0.5 * Math.cos(x);
                array[i][0] = x;
                array[i][1] = y;
                x+=step;
            }
        }
        //вывод в табличном виде
        System.out.printf("%-10s%-25s%n","Аргумент","Значение");
        System.out.println("-----------------------------------------------------");
        for (int i = 0; i < array.length; i++)
        {
            System.out.printf("%-10.2f%-27.2f%n", array[i][0], array[i][1]);
        }
    }
}
