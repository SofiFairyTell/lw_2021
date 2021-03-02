package ru.bstu.it32.kurbatova.lab1;

import java.util.logging.*;

public class LoggerClass {
    private static Logger setLog(String loggerName) {
        Logger log =  Logger.getLogger(loggerName) ;
        log.setLevel(Level.FINE);
        log.setUseParentHandlers(false);
        return log;
    }


}
