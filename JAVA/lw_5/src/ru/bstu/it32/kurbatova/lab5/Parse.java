package ru.bstu.it32.kurbatova.lab5;
import java.sql.ResultSet;
import java.util.ArrayList;
public class Parse
{
    protected ArrayList<Eventlist> eventslist = new ArrayList<Eventlist>();
    protected ParseDOM parseDOM;

    public Parse(ArrayList<Eventlist> eventsXML) {
        this.eventslist = eventsXML;
    }

    public Parse(ArrayList<Eventlist> eventsXML, ParseDOM parseDOM) {
        this.eventslist = eventsXML;
        this.parseDOM = parseDOM;
    }

    public void parseXMLtoDB() {
        var sqlOBJ = new ParseSQL();
        for (Eventlist eventlist : this.eventslist) {
            try {
                sqlOBJ.addNewRecord(eventlist);
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
                this.eventslist.add(new Eventlist(
                        result.getInt("id"),
                        result.getString("event_name"),
                        result.getString("event_type"),
                        result.getString("date_start"),
                        result.getString("date_end"),
                        result.getString("manager"),
                        result.getString("place")
                ));
            }
            this.parseDOM.setDomNodes(this.eventslist);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
