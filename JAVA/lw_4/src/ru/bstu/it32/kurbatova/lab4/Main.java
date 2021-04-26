package ru.bstu.it32.kurbatova.lab4;

import java.io.*;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

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
 *<img.*?src?= ?['\"]([^'\"]*)['\"](.*?)\/ - будет две группы
 * (?|(width.*)|(class.*)|(alt.*)|(height.*))\/ - найдет полностью последнуюю группу
 * 100, 200 и 300 это значения введенные пользователем
 * */
public class Main {

    public static void main(String[] args) throws IOException {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Введите путь к HTML файлу: ");
        String filePath = scanner.nextLine();
        System.out.println("Введите высоту и ширину изображений");
        Parametres param = new Parametres();
        param.Parametres(scanner);
        String replacement = " width = '"+param.Width()+"' height = '"+param.Height()+"'";
        Parser parse = new Parser();
        parse.HtmlParser(filePath, replacement);

    }
}
