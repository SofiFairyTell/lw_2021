package ru.bstu.it32.kurbatova.lab1;

//Новый класс для исключений связанных с неправильным вводом
class InputException extends Exception
{
    InputException(String message)
    {
        super(message);
    }
}