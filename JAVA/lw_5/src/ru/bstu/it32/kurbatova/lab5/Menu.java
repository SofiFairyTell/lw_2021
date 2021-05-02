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

public class Menu
{
    public static int choiceMenu() {
        System.out.println("Выберите с чем работать: \n" +
                "1: XML\n" +
                "2: БД\n" +
                "3: Конвертировать данные из XML в БД\n" +
                "4: Конвертировать данные из БД в XML\n" +
                "5: Завершить работу.");
        int type = 0;
        while (true) {
            type = Common.getIDevent();
            if (type >= 1 && type <= 5) {
                return type;
            }
            System.out.println("Можно ввести только 1,2,3,4,5");
        }
    }

    public static void start() {
        SetData set = new SetData();
        var prop = new PropertiesParse();
        var catalog = prop.readCatalogRoot();
        String filePath = catalog + "\\file.xml";
        int type = choiceMenu();
        if (type == 3) {
            var sax = new ParseSAX();
            var parsing = new Parsing(sax.readerSaxDocument(filePath));
            parsing.parseXMLtoDB();
            start();
        }
        if (type == 4) {
            var sax = new ParseSAX();
            var dom = new ParseDOM(filePath);
            var parsing = new Parsing(sax.readerSaxDocument(filePath), dom);
            parsing.parseDBtoXML();
            start();
        }
        if (type == 5) return;
        while (true) {
            System.out.println("Выберите действие: \n" +
                    "1: Вывести всё содержимое\n" +
                    "2: Найти содержимое по параметру\n" +
                    "3: Добавить новую запись\n" +
                    "4: Изменить запись\n" +
                    "5: Удалить запись\n" +
                    "9: Выбрать заново с чем работать\n" +
                    "0: Завершить работу\n");
            var choice = Common.getIDevent();
            switch (choice) {
                case 1: {
                    if (type == 1) {
                        var sax = new ParseSAX();
                        var events = sax.readerSaxDocument(filePath);
                        if (events.size() > 0) {
                            for (Event event : events) {
                                System.out.println(events.toString());
                            }
                        }
                    } else if (type == 2) {
                        var mySqlObj = new MySqlParse();
                        var result = mySqlObj.workDataBase(choice);
                        try {
                            while (result.next()) {
                                Event event = new Event(
                                        result.getInt("id"),
                                        result.getString("name"),
                                        result.getString("type"),
                                        Common.DateParser(result.getString("date_start")),
                                        Common.DateParser(result.getString("date_end")),
                                        result.getString("manager"),
                                        result.getString("place")
                                );

                                System.out.println(event.toString());
                            }
                        } catch (Exception e) {
                            e.printStackTrace();
                        }
                    }
                }
                break;
                case 2: {
                    if (type == 1) {
                        var sax = new ParseSAX();
                        String content = "";
                        System.out.print("Выберите содержимое поиска (id):\n");
                        Scanner scanner = new Scanner(System.in);
                        content = scanner.nextLine();
                        var event = sax.searchSaxDocument(filePath, content);
                        System.out.println(event != null ? event.toString() : "Такого события нет!");
                    } else if (type == 2) {
                        var mySqlObj = new MySqlParse();
                        var result = mySqlObj.workDataBase(choice);
                        try {
                            while (result.next()) {
                                Event event = new Event(
                                        result.getInt("id"),
                                        result.getString("name"),
                                        result.getString("type"),
                                        Common.DateParser(result.getString("date_start")),
                                        Common.DateParser(result.getString("date_end")),
                                        result.getString("manager"),
                                        result.getString("place")
                                );
                                System.out.println(event.toString());
                            }
                        } catch (Exception e) {
                            e.printStackTrace();
                        }
                    }
                }
                break;
                case 3: {
                    if (type == 1) {
                        var sax = new ParseSAX();
                        var events = sax.readerSaxDocument(filePath);

                        var newEvent = set.setNewEvent(events.size());
                        events.add(newEvent);
                        var dom = new ParseDOM(filePath);
                        dom.setDomNodes(events);
                    } else if (type == 2) {
                        var mySqlObj = new MySqlParse();
                        mySqlObj.workDataBase(choice);
                    }
                }
                break;
                case 4: {
                    if (type == 1) {
                        set.changeEvent(filePath);
                    } else if (type == 2) {
                        var mySqlObj = new MySqlParse();
                        mySqlObj.workDataBase(choice);
                    }
                }
                break;
                case 5: {
                    if (type == 1) {
                        set.deleteEvent(filePath);
                    } else if (type == 2) {
                        var mySqlObj = new MySqlParse();
                        mySqlObj.workDataBase(choice);
                    }
                }
                break;
                case 9: {
                    start();
                }
                break;
                case 0: {
                    return;
                }
            }
        }
    }
}
