package ru.bstu.it32.kurbatova.lab5;
import java.sql.*;

public class ParseSQL
{
    private  String connectionUrl;
    private  String userName ;
    private  String password ;
    private  Statement statement;

    ParseSQL()
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
        return this.statement.executeQuery("select * from eventslist");
    }

    public ResultSet searchRecord(int id) throws SQLException {
        return statement.executeQuery("select * from eventslist where id in(" + id + ");");
    }

    public void addNewRecord(String[] strings) throws SQLException {
        this.statement.executeUpdate("INSERT INTO eventslist (name, type, date_start, date_end, manager , place)" +
                " VALUES ('" + strings[0] + "','" + strings[1] + "', '" + strings[2] + "', '" + strings[3] + "', " +
                "'" + strings[4] + "','" + strings[5] + "')");
    }

    public void addNewRecord(Eventlist eventlist) throws SQLException {
        statement.executeUpdate("INSERT INTO eventslist (name, type, date_start, date_end, manager , place)" +
                " VALUES ('" + eventlist.name + "','" + eventlist.type + "', '" + eventlist.date_start + "', '" + eventlist.date_end + "', " +
                "'" + eventlist.manager + "','" + eventlist.place + "')");
    }

    public void updateRecord(int id) throws SQLException {
        SetData setData = new SetData();
        var strings = setData.setData();
        statement.executeUpdate("update eventslist set name = '" + strings[0] + "', type = '" + strings[1] + "', date_start = '" + strings[2]
                + "', date_end = '" + strings[3] + "', manager = '" + strings[4] + "', place = '" + strings[5] + "' where id = " + id + ";");
    }

    public void deleteRecord(int id) throws SQLException {
        statement.executeUpdate("delete from eventslist where id in(" + id + ");");
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