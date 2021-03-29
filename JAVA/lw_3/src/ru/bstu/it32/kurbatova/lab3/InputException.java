package ru.bstu.it32.kurbatova.lab1;


public class InputException extends Exception
{
    private final String message;

    /**
 *  Новый класс для исключений связанных с неправильным вводом
 *
 * */

    InputException(String message)
    {
        super(message);
        this.message = message;
    }
}