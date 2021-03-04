package ru.bstu.it32.kurbatova.lab1;

import java.io.IOException;
import java.text.MessageFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.logging.*;

public class LoggerClass {
    public static Logger setLog(String loggerName)
    {
        Logger log =  Logger.getLogger(loggerName) ;
        log.setLevel(Level.FINE);
        log.setUseParentHandlers(false);

        FileHandler fileHandler = null;
        try
        {
            fileHandler = new FileHandler("./_log/"+loggerName +".txt",true);
        }
        catch(IOException e)
        {
            e.printStackTrace();
        }
        if (fileHandler != null)
        {
            fileHandler.setLevel(Level.INFO);
            fileHandler.setFormatter(new Format() );
        }
        log.addHandler(fileHandler);
        FileHandler fileHandler1 = null;
        try
        {
            fileHandler1 = new FileHandler("./_log/"+loggerName + "Full"+".txt",true);
        } catch (IOException e) {
            e.printStackTrace();
        }
        if (fileHandler1 != null)
        {
            fileHandler1.setLevel(Level.FINE);
            fileHandler1.setFormatter(new Format());
            log.addHandler(fileHandler1);
        }
        ConsoleHandler consoleHandler = new ConsoleHandler();
        consoleHandler.setLevel(Level.FINE);
        consoleHandler.setFormatter(new Format());
        log.addHandler(consoleHandler);
        return log;
    }

static  class Format extends Formatter
{
        @Override
        public String format(LogRecord record)
        {
            Date currentDate = new Date();
            SimpleDateFormat timeFormat = new SimpleDateFormat("E yyyy.MM.dd hh:mm:ss a zzz");
            String output;
            output = String.format("LEVEL: %-10s Date: %-10s  Class_name: %-10s  Text:  %-10s  ", record.getLevel(),timeFormat.format(currentDate), record.getSourceClassName(),record.getMessage());
            if (record.getThrown()!=null)
            {
                output += " EXCEPTION";
                StackTraceElement[] stackTraceElements = record.getThrown().getStackTrace();
                for (StackTraceElement traceElement:stackTraceElements)
                    output += traceElement.toString() +"\n";
            }
            output += "\n\n";
            return output;
        }
    }
}
