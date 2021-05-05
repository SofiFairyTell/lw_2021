package ru.bstu.it32.kurbatova.lab5;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

public class Eventlist
{
    protected int id;
    protected String event_name;
    protected String event_type;
    //protected Date date_start;
    protected String date_start;
    //protected Date date_end;
    protected String date_end;
    protected String manager;
    protected String place;

//    public Eventlist(int id, String name, String type, Date date_start, Date date_end, String manager, String place)
//    {
//        this.id = id;
//        this.event_name = name;
//        this.event_type = type;
//        this.date_start = date_start;
//        this.date_end = date_end;
//        this.manager = manager;
//        this.place = place;
//    }
    public Eventlist(int id, String name, String type, String date_start, String date_end, String manager, String place)
    {
        this.id = id;
        this.event_name = name;
        this.event_type = type;
        this.date_start = date_start;
        this.date_end = date_end;
        this.manager = manager;
        this.place = place;
    }
    public Eventlist(int id, String name, String type,  String manager, String place)
    {
        this.id = id;
        this.event_name = name;
        this.event_type = type;
        this.date_end = Common.DateToString(Calendar.getInstance().getTime());
        this.date_start = Common.DateToString(Calendar.getInstance().getTime());
        this.manager = manager;
        this.place = place;
    }
    @Override
    public  String toString()
    {
        SimpleDateFormat ft = new SimpleDateFormat("dd-MM-yyyy hh:mm:ss");

        return  "ID:" + this.id + "\n"
                + "Название: " + this.event_name + "\n"
                + "Тип: " + this.event_type + "\n"
                + "Дата и время начала: " + this.date_start + "\n"
                + "Дата и время конца: " + this.date_end + "\n"
                + "Организатор: " + this.manager + "\n"
                + "Место проведения: " + this.place + "\n";

    }

    public int getId()
    {
        return this.id;
    }
    public String getName()
    {
        return  this.event_name;
    }
    public  String getType()
    {
        return  this.event_type;
    }
    public String getDate_start()
    {
        return this.date_start;
    }
    public String getDate_end()
    {
        return this.date_end;
    }
    public  String getManager()
    {
        return this.manager;
    }
    public String getPlace()
    {
        return this.place;
    }
}
