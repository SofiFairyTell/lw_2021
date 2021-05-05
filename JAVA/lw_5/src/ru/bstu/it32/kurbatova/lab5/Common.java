package ru.bstu.it32.kurbatova.lab5;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Scanner;

public class Common {
    public static int getIDevent() {
        Scanner sc = new Scanner(System.in);
        while (!sc.hasNextInt()) {
            System.out.println("Введенно некоректное значение!");
            System.out.print("Введите значение повторно: ");
            sc.next();
        }
        return sc.nextInt();
    }

    public static Date DateParser(String date_str)
    {
        Date date_parsed = null;
        //SimpleDateFormat dateFormat = new SimpleDateFormat("dd-MM-yyyy hh:mm:ss");
        SimpleDateFormat dateFormat = new SimpleDateFormat("dd.MM.yyyy");
        try {
            date_parsed = dateFormat.parse(date_str);
        } catch (ParseException e) {
            System.out.println("Не удалось извлечь дату " + dateFormat);
        }
        return date_parsed;
    }

    public static  String DateToString(Date date)
    {
        String date_parsed = null;
        SimpleDateFormat dateFormat = new SimpleDateFormat("dd.MM.yyyy hh:mm:ss");
        date_parsed = dateFormat.format(date);
        return date_parsed;
    }
}
