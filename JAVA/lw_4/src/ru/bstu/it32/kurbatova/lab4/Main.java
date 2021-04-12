package ru.bstu.it32.kurbatova.lab4;

import java.io.FileNotFoundException;
import java.util.Scanner;

/**
 * На вход программе подается произвольный html-файл. Необходимо всем тегам <img> добавить недостающие атрибуты
 * height и width со значениями заданными пользователем.
 * Пример:
 * <img src='kartinka.jpg' height='100'/>
 * <img src='kartinka.jpg' width='100'/>
 * <img src='kartinka.jpg' />
 * На выходе:
 * <img src='kartinka.jpg' height='100' width='200'/>
 * <img src='kartinka.jpg' height='300' width='100'/>
 * <img src='kartinka.jpg' height='200' width='300'/>
 *
 * 100, 200 и 300 это значения введенные пользователем*/
public class Main {
    private void FileReader(String filename)
    {

    }
    private void FileParser(String line)
	{
		String Str = new String("<img src='kartinka.jpg' />");
		int index = Str.indexOf("' ");
		int index2 = Str.indexOf("/");
		System.out.print(index);
		System.out.print(index2);
		System.out.print("\nВозвращаемое значение: ");
		Str = Str.replace(Str.substring(index+1,index2), " width = '300' height = '100'");
		System.out.println(Str);
	}
	
    public static void main(String[] args) throws FileNotFoundException {
        Scanner scanner = new Scanner(System.in);
        String path = "C:\\Users\\Kurbatova\\source\\LW2020\\lw_2021\\TCS\\LAB_1\\TRAVEL_WEB";
        String pattern = "<img.*?src?= ?['\\\"]([^'\\\"]*)['\\\"](.*?)\\/";
    }
}
