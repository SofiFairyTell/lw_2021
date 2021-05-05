package ru.bstu.it32.kurbatova.lab5;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

public class Eventlist
{
    protected int id;
    protected String name;
    protected String type;
    protected Date date_start;
    protected Date date_end;
    protected String manager;
    protected String place;

    public Eventlist(int id, String name, String type, Date date_start, Date date_end, String manager, String place)
    {
        this.id = id;
        this.name = name;
        this.type = type;
        this.date_start = date_start;
        this.date_end = date_end;
        this.manager = manager;
        this.place = place;
    }
    public Eventlist(int id, String name, String type, String date_start, String date_end, String manager, String place)
    {
        this.id = id;
        this.name = name;
        this.type = type;
        this.date_start = Common.DateParser(date_start);
        this.date_end = Common.DateParser(date_end);
        this.manager = manager;
        this.place = place;
    }
    public Eventlist(int id, String name, String type,  String manager, String place)
    {
        this.id = id;
        this.name = name;
        this.type = type;
        this.date_end = Calendar.getInstance().getTime();
        this.date_start = Calendar.getInstance().getTime();
        this.manager = manager;
        this.place = place;
    }
    @Override
    public  String toString()
    {
        SimpleDateFormat ft = new SimpleDateFormat("dd.MM.yyyy hh:mm:ss");

        return  "ID:" + this.id + "\n"
                + "Название: " + this.name + "\n"
                + "Тип: " + this.type + "\n"
                + "Дата и время начала: " + ft.format(this.date_start) + "\n"
                + "Дата и время конца: " + ft.format(this.date_end) + "\n"
                + "Организатор: " + this.manager + "\n"
                + "Место проведения: " + this.place + "\n";

    }

    public int getId()
    {
        return this.id;
    }
    public String getName()
    {
        return  this.name;
    }
    public  String getType()
    {
        return  this.type;
    }
    public Date getDate_start()
    {
        return this.date_start;
    }
    public Date getDate_end()
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