package ru.bstu.it32.kurbatova.lab1;

//Новый класс для исключений связанных с неправильным вводом
public class InputException extends Exception
{
    InputException(String message)
    {
        super(message);
    }
}