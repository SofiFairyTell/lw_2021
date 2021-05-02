package ru.bstu.it32.kurbatova.lab5;
import java.sql.ResultSet;
import java.util.ArrayList;
public class Parse
{
    protected ArrayList<Event> events = new ArrayList<Event>();
    protected ParseDOM parseDOM;

    public Parse(ArrayList<Event> eventsXML) {
        this.events = eventsXML;
    }

    public Parse(ArrayList<Event> eventsXML, ParseDOM parseDOM) {
        this.events = eventsXML;
        this.parseDOM = parseDOM;
    }

    public void parseXMLtoDB() {
        var sqlOBJ = new ParseSQL();
        for (Event event : this.events) {
            try {
                sqlOBJ.addNewRecord(event);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    public void parseDBtoXML() {
        var sqlOBJ = new ParseSQL();
        try {
            var result = sqlOBJ.getAll();
            while (result.next()) {
                this.events.add(new Event(
                        result.getInt("id"),
                        result.getString("name"),
                        result.getString("type"),
                        Common.DateParser(result.getString("date_start")),
                        Common.DateParser(result.getString("date_end")),
                        result.getString("manager"),
                        result.getString("place")
                ));
            }
            this.parseDOM.setDomNodes(this.events);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
