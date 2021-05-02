package ru.bstu.it32.kurbatova.lab5;

import java.io.FileInputStream;
import java.io.IOException;
import java.util.Properties;

public class ParseProperties
{
    private String propPath = "C:\\Users\\Kurbatova\\source\\LW2021\\JAVA\\lw_5\\settings.properties";

    public String readCatalogRoot () {
        Properties prop = new Properties();
        try {
            FileInputStream fis = new FileInputStream(propPath);
            prop.load(fis);
            return new String(prop.getProperty("rootCatalog").getBytes("ISO8859-1"));
        } catch (IOException e) {
            System.out.println("Ошибка в программе: файл не найден");
            e.printStackTrace();
        }
        return "";
    }
    public String[] bdSettings() {
        Properties prop = new Properties();
        try {
            //обращение к файлу и получение данных
            FileInputStream fis = new FileInputStream(propPath);
            prop.load(fis);
            // взятие свойства и преобразование в необходимую кодировку
            String uri = new String(prop.getProperty("connectionUrl").getBytes("ISO8859-1"));
            String name = new String(prop.getProperty("userName").getBytes("ISO8859-1"));
            String password = new String(prop.getProperty("password").getBytes("ISO8859-1"));
            String[] propStr = {uri,name,password};
            return propStr;

        } catch (IOException e) {
            System.out.println("Ошибка в программе: файл не найден");
            e.printStackTrace();
        }
        String[] propStr = {};
        return propStr;
    }
    public String errorDriver() {
        Properties prop = new Properties();
        try {
            FileInputStream fis = new FileInputStream(propPath);
            prop.load(fis);
            return new String(prop.getProperty("errorDriver").getBytes("ISO8859-1"));
        } catch (IOException e) {
            System.out.println("Ошибка в программе: файл не найден");
            e.printStackTrace();
        }
        return "";
    }

    public String error() {
        Properties prop = new Properties();
        try {
            FileInputStream fis = new FileInputStream(propPath);
            prop.load(fis);
            return new String(prop.getProperty("error").getBytes("ISO8859-1"));
        } catch (IOException e) {
            System.out.println("Ошибка в программе: файл не найден");
            e.printStackTrace();
        }
        return "";
    }
}
