package ru.bstu.it32.kurbatova.lab1;

import org.jetbrains.annotations.NotNull;

import java.io.IOException;
import java.text.MessageFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.logging.*;

/**
 * <p>Описание класса Logger Class</p>
 * Содержит методы для создания логов в процессе выполнения приложения. */
public class LoggerClass {
    /***
     * <p>Опиание метода setLog</p>
     * @param loggerName имя файла для записи лога
     * @return log объекта класса Logger
     */
    @NotNull
    public static Logger setLog(String loggerName)
    {
        Logger log =  Logger.getLogger(loggerName) ;
        log.setLevel(Level.FINE);
        log.setUseParentHandlers(false);

        FileHandler fileHandler = null;
        try
        {
            fileHandler = new FileHandler("./"+loggerName +".txt",true);
        }
        catch(IOException e)
        {
            e.printStackTrace();
        }
        if (fileHandler != null)
        {
            fileHandler.setLevel(Level.FINE);
            fileHandler.setFormatter(new Format() );
        }
        log.addHandler(fileHandler);
        FileHandler fileHandler1 = null;
        try
        {
            fileHandler1 = new FileHandler("./"+loggerName + "WARNING"+".txt",true);
        } catch (IOException e) {
            e.printStackTrace();
        }
        if (fileHandler1 != null)
        {
            fileHandler1.setLevel(Level.SEVERE);
            fileHandler1.setFormatter(new Format());
            log.addHandler(fileHandler1);
        }
        ConsoleHandler consoleHandler = new ConsoleHandler();
        consoleHandler.setLevel(Level.FINE);
        consoleHandler.setFormatter(new Format());
        log.addHandler(consoleHandler);
        return log;
    }
    /**
     * <p>Описание класса Format </p>
     * Является наследником класса Formatter. Методы определяют вид объекта класса LogRecord */
static  class Format extends Formatter
{
    /**
     * <p>Описание метода format</p>
     * @param record объект класса LogRecord
     * @return output строка для записи в текстовый документ или для вывода на экран*/
        @Override
        public String format(LogRecord record)
        {
            Date currentDate = new Date();
            SimpleDateFormat timeFormat = new SimpleDateFormat("E yyyy.MM.dd hh:mm:ss a zzz");
            String output;
            output = String.format("%-10s Date: %-10s  Class_name: %-10s  Text:  %-10s  ", record.getLevel(),timeFormat.format(currentDate), record.getSourceClassName(),record.getMessage());
            if (record.getThrown()!=null)
            {
                output += " ERROR";
                StackTraceElement[] stackTraceElements = record.getThrown().getStackTrace();
                for (StackTraceElement traceElement:stackTraceElements)
                    output += traceElement.toString() +"\n";
            }
            output += "\n\n";
            return output;
        }
    }
}
