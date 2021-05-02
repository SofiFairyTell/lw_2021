package ru.bstu.it32.kurbatova.lab5;


import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Scanner;

import javax.xml.parsers.*;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

public class SetData {
    public String setValue()
    {
        while (true)
        {
            Scanner input = new Scanner(System.in);
            String str = input.next();
            if(str.length()>0)
            {
                return str;
            }
            else
            {
                System.out.println("Пустые значения не допустимы");
            }
        }
    }



    public String[] setData()
    {
        String[] strings = new String[6];
        System.out.println("Введите данные о событии:");

        System.out.println("Введите Название:");
        strings[0] = setValue();
        System.out.println("Введите Тип:");
        strings[1] = setValue();
        System.out.println("Введите Дату начала в формате: ГОД.МЕСЯЦ.ДЕНЬ ЧАСЫ:МИНУТЫ:СЕКУНДЫ");
        strings[2] = setValue();
        System.out.println("Введите Дату конца в формате: ГОД.МЕСЯЦ.ДЕНЬ ЧАСЫ:МИНУТЫ:СЕКУНДЫ");
        strings[3] = setValue();
        System.out.println("Введите организатора:");
        strings[4] = setValue();
        System.out.println("Введите место:");
        strings[5] = setValue();
        return strings;
    }

    private Date DateParser(String date_str)
    {
        Date date_parsed = null;
        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd");
        try {
            date_parsed = dateFormat.parse(date_str);
        } catch (ParseException e) {
            System.out.println("Не удалось извлечь дату " + dateFormat);
        }
        return date_parsed;
    }
    private Event setNewEvent(int size)
    {
        var strings = this.setData();
        Date date_start = null, date_end = null;
        date_start = this.DateParser(strings[2]);
        date_end = this.DateParser(strings[3]);
//        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd");
//        try {
//            date_start = dateFormat.parse(strings[2]);
//            date_end = dateFormat.parse(strings[3]);
//        } catch (ParseException e) {
//            System.out.println("Не удалось извлечь дату " + dateFormat);
//        }
        return new Event(size + 1, strings[0], strings[1],date_start, date_end , strings[4], strings[5]);
    }

    private void changeEvent(String filePath) {
       // var sax = new SAXParse();
        //var events = sax.readerSaxDocument(filePath);
        System.out.println("Введите id события:");
        var searchId = this.getID();
        var strings = this.setData();
        boolean flag = false;
        for (int i = 0; i < events.size(); i++) {
            if (events.get(i).getId() == searchId) {
                events.set(i, new Event(searchId,
                        strings[0], strings[1], this.DateParser(strings[2]),
                        this.DateParser(strings[3]), strings[4], strings[5]));
                flag = true;
                break;
            }
        }
        if (flag) {
            var dom = new DomParse(filePath);
            dom.setDomNodes(events);
        } else {
            System.out.println("Такого события нет!");
        }

    }

    public static int getID() {
        Scanner sc = new Scanner(System.in);
        while (!sc.hasNextInt()) {
            System.out.println("Введенно некоректное значение!");
            System.out.print("Введите значение повторно: ");
            sc.next();
        }
        return sc.nextInt();
    }

}
