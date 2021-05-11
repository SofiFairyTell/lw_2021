package ru.bstu.it32.kurbatova.lab5;


import java.util.Scanner;

public class Menu
{
    public static int choiceMenu() {
        System.out.println("Выберите с чем работать: \n" +
                "1. XML\n" +
                "2. БД\n" +
                "3. Конвертировать данные из XML в БД\n" +
                "4. Конвертировать данные из БД в XML\n" +
                "5. Завершить работу.");
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
        var prop = new ParseProperties();
        var catalog = prop.readCatalogRoot();
        String filePath = catalog + "\\file.xml";
        int type = choiceMenu();
        if (type == 3) {
            var sax = new ParseSAX();
            var parsing = new Parse(sax.readerSaxDocument(filePath));
            parsing.parseXMLtoDB();
            start();
        }
        if (type == 4) {
            var sax = new ParseSAX();
            var dom = new ParseDOM(filePath);
            var parsing = new Parse(sax.eventslist,dom);
            parsing.parseDBtoXML();
            start();
        }
        if (type == 5) return;
        while (true) {
            System.out.println("Выберите действие: \n" +
                    "1. Вывести всё содержимое\n" +
                    "2. Найти содержимое по параметру\n" +
                    "3. Добавить новую запись\n" +
                    "4: Изменить запись\n" +
                    "5: Удалить запись\n" +
                    "6: Возврат в верхнее меню\n" +
                    "0: Завершить работу\n");
            var choice = Common.getIDevent();
            switch (choice) {
                case 1: {
                    if (type == 1) {
                        var sax = new ParseSAX();
                        var eventslist = sax.readerSaxDocument(filePath);
                        if (eventslist.size() > 0) {
                            for (Eventlist eventlist : eventslist) {
                                System.out.println(eventlist.toString());
                            }
                        }
                    } else if (type == 2) {
                        var mySqlObj = new ParseSQL();
                        var result = mySqlObj.workDataBase(choice);
                        try {
                            while (result.next()) {
                                Eventlist eventlist = new Eventlist(
                                        result.getInt("id"),
                                        result.getString("event_name"),
                                        result.getString("event_type"),
                                        result.getString("date_start"),
                                        result.getString("date_end"),
                                        result.getString("manager"),
                                        result.getString("place")
                                );

                                System.out.println(eventlist.toString());
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
                    } else
                        if (type == 2) {
                        var mySqlObj = new ParseSQL();
                        var result = mySqlObj.workDataBase(choice);
                        try {
                            while (result.next()) {
                                Eventlist eventlist = new Eventlist(
                                        result.getInt("id"),
                                        result.getString("event_name"),
                                        result.getString("event_type"),
                                        result.getString("date_start"),
                                        result.getString("date_end"),
                                        result.getString("manager"),
                                        result.getString("place")
                                );
                                System.out.println(eventlist.toString());
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
                        var eventslist = sax.readerSaxDocument(filePath);

                        var newEvent = set.setNewEvent(eventslist.size());
                        eventslist.add(newEvent);
                        var dom = new ParseDOM(filePath);
                        dom.setDomNodes(eventslist);
                    } else if (type == 2) {
                        var mySqlObj = new ParseSQL();
                        mySqlObj.workDataBase(choice);
                    }
                }
                break;
                case 4: {
                    if (type == 1) {
                        set.changeEvent(filePath);
                    } else if (type == 2) {
                        var mySqlObj = new ParseSQL();
                        mySqlObj.workDataBase(choice);
                    }
                }
                break;
                case 5: {
                    if (type == 1) {
                        set.deleteEvent(filePath);
                    } else if (type == 2) {
                        var mySqlObj = new ParseSQL();
                        mySqlObj.workDataBase(choice);
                    }
                }
                break;
                case 6: {
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
