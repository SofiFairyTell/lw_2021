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
        switch(mark)
        {
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
}
