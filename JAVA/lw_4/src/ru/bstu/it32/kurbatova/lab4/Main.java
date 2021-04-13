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
 * 100, 200 и 300 это значения введенные пользователем*/
public class Main {

    public static void main(String[] args) throws IOException {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Введите путь к HTML файлу: ");
        String filePath = scanner.nextLine();
        BufferedReader bufferedReader = new BufferedReader(new FileReader(filePath));

        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter("result.html"));

        String patt = "<img.*?src?= ?['\\\"]([^'\\\"]*)['\\\"](.*?)\\/";
        //Разбить паттерна три группы! Тогда  первой группе д.б. img + src, потом вставка наших значений и соединение со второй группой
        Pattern pattern = Pattern.compile(patt);
        Matcher matcher;

        String input = "";
        StringBuilder result = new StringBuilder();
        while ((input = bufferedReader.readLine()) != null) {
            matcher = pattern.matcher(input);
            if (matcher.find())
            {
                String group = matcher.group(2);
                input = input.replaceAll(matcher.group(2)," width = '300' height = '100'");
                System.out.println(input);
                result.append(input).append("\n");
            }
            else
            {
                result.append(input).append("\n");
            }

        }
        System.out.println(result);
        bufferedWriter.write(result.toString());
        bufferedWriter.close();
    }
}
