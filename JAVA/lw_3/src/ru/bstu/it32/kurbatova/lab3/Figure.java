package ru.bstu.it32.kurbatova.lab3;

import java.util.Scanner;

public abstract class Figure {
     public abstract void init(Scanner scanner);	// считывание параметров с консоли
     public abstract String getPerimetr();	// возвращает  периметр
     public String toString(); 		// возвращается состояние объекта в виде строки
}
