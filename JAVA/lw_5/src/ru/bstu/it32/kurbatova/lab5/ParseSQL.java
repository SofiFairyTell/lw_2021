package ru.bstu.it32.kurbatova.lab5;
import java.sql.*;

public class ParseSQL
{
    private  String connectionUrl;
    private  String userName ;
    private  String password ;
    private  Statement statement;

    public ParseSQL()
    {

        try {
            ParseProperties propertiesParse = new ParseProperties();
            var settings = propertiesParse.bdSettings();
            this.connectionUrl = settings[0];
            this.userName = settings[1];
            this.password = settings[2];
            Connection connection = DriverManager.getConnection(connectionUrl, userName, password);
            System.out.println("Подключение прошло успешно!");
            this.statement = (Statement) connection.createStatement();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public ResultSet getAll() throws SQLException {
        return this.statement.executeQuery("select * from eventslist.eventslist");
    }

    public ResultSet searchRecord(int id) throws SQLException {
        return statement.executeQuery("select * from eventslist.eventslist where id in(" + id + ");");
    }

    public void addNewRecord(String[] strings) throws SQLException {
        this.statement.executeUpdate("INSERT INTO eventslist.eventslist (event_name, event_type, date_start, date_end, manager , place)" +
                " VALUES ('" + strings[0] + "','" + strings[1] + "', '" + strings[2] + "', '" + strings[3] + "', " +
                "'" + strings[4] + "','" + strings[5] + "')");
    }

    public void addNewRecord(Eventlist eventlist) throws SQLException {
        statement.executeUpdate("INSERT INTO eventslist.eventslist (event_name, event_type, date_start, date_end, manager , place, id)" +
                " VALUES ('" + eventlist.event_name + "','" + eventlist.event_type + "', '" + eventlist.date_start + "', '" + eventlist.date_end + "', " +
                "'" + eventlist.manager + "','" + eventlist.place + "','" + eventlist.id +"')");
    }

//    public void addNewRecord(lace + "') where id <>("+eventlist.id+")");
////    }Eventlist eventlist) throws SQLException {
//        statement.executeUpdate("INSERT INTO eventslist.eventslist (event_name, event_type, date_start, date_end, manager , place)" +
//                " VALUES ('" + eventlist.event_name + "','" + eventlist.event_type + "', '" + eventlist.date_start + "', '" + eventlist.date_end + "', " +
//                "'" + eventlist.manager + "','" + eventlist.p
    public void updateRecord(int id) throws SQLException {
        SetData setData = new SetData();
        var strings = setData.setData();
        statement.executeUpdate("update eventslist.eventslist set event_name = '" + strings[0] + "', event_type = '" + strings[1] + "', date_start = '" + strings[2]
                + "', date_end = '" + strings[3] + "', manager = '" + strings[4] + "', place = '" + strings[5] + "' where id = " + id + ";");
    }
    public void updateRecord(int id, Eventlist eventlist) throws SQLException {
        statement.executeUpdate("update eventslist.eventslist set event_name = '" + eventlist.event_name + "', event_type = '" + eventlist.event_type
                + "', date_start = '" +eventlist.date_start   + "', date_end = '" + eventlist.date_end + "', manager = '" + eventlist.manager +
                "', place = '" + eventlist.place  + "' where id = " + id + ";");
    }
    public void deleteRecord(int id) throws SQLException {
        statement.executeUpdate("delete from eventslist.eventslist where id in(" + id + ");");
    }

    public ResultSet workDataBase(int action) {
        try {
            //регистрация драйвера
            //Class.forName("com.mysql.cj.jdbc.Driver");
            Class.forName("org.postgresql.Driver");
            try {
                switch (action) {
                    case 1 -> {
                        return getAll();
                    }
                    case 2 -> {
                        System.out.println("Введите Id записи");
                        var id = Common.getIDevent();
                        return searchRecord(id);
                    }
                    case 3 -> {
                        SetData setData = new SetData();
                        var strings = setData.setData();
                        addNewRecord(strings);
                    }
                    case 4 -> {
                        System.out.println("Введите Id записи");
                        var id = Common.getIDevent();
                        updateRecord(id);
                    }
                    case 5 -> {
                        System.out.println("Введите Id записи");
                        var id = Common.getIDevent();
                        deleteRecord(id);
                    }
                }
            } catch (Exception e) {
                var prop = new ParseProperties();
                System.out.println(prop.error());
            }
        } catch (Exception e) {
            var prop = new ParseProperties();
            System.out.println(prop.errorDriver());
        }
        return null;
    }
}
