package ru.bstu.it32.kurbatova.lab5;

import java.text.SimpleDateFormat;
import java.util.Date;

public class Event
{
    protected int id;
    protected String name;
    protected String type;
    protected Date date_start;
    protected Date date_end;
    protected String manager;
    protected String place;

    public Event(int id, String name, String type, Date date_start, Date date_end, String manager, String place)
    {
        this.id = id;
        this.name = name;
        this.type = type;
        this.date_start = date_start;
        this.date_end = date_end;
        this.manager = manager;
        this.place = place;
    }

    @Override
    public  String toString()
    {
        SimpleDateFormat ft = new SimpleDateFormat("E yyyy.MM.dd 'at' hh:mm:ss a zzz");

        return  "ID:" + this.id + "\n"
                + "Название: " + this.name + "\n"
                + "Тип: " + this.type + "\n"
                + "Дата и время начала: " + ft.format(this.date_start) + "\n"
                + "Дата и время конца: " + ft.format(this.date_end) + "\n"
                + "Организатор: " + this.manager + "\n"
                + "Место проведения" + this.place + "\n";

    }

}
