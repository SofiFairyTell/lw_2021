package sample;

import javafx.fxml.FXML;
import javafx.scene.control.*;
import ru.bstu.it32.kurbatova.lab5.*;

import java.io.IOException;
import java.sql.SQLException;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;

public class Controller
{



    @FXML
    private TextField event_name_TA;
    @FXML
    private DatePicker date_start_TA_pick;
    @FXML
    private DatePicker date_end_TA_pick;
    @FXML
    private TextField manager_TA;
    @FXML
    private TextField place_TA;
    @FXML
    private TextArea calendarArea;
    @FXML
    private  TextField id_TA;
    @FXML
    private ComboBox event_type_CB;
    @FXML
    private CheckBox choose_BD;
@FXML
    public void WatchAll(javafx.event.ActionEvent actionEvent) throws IOException {
        if(calendarArea != null)
        {
            calendarArea.clear();
        }
        if(choose_BD.isSelected())
        {
            var mySqlObj = new ParseSQL();

            var result = mySqlObj.workDataBase(1);
            try {
                while (result.next()) {
                    Eventlist eventlist = new Eventlist(
                            result.getInt("id"),
                            result.getString("event_name"),
                            result.getString("event_type"),
                            result.getString("date_start"),
                            result.getString("date_end"),
                            result.getString("manager"),
                            result.getString("place")
                    );
                    calendarArea.appendText(eventlist.toString() + "\n");
                }
                } catch (Exception e) {
                    e.printStackTrace();
                }
        }
        else {
            var prop = new ParseProperties();
            var catalog = prop.readCatalogRoot();
            var sax = new ParseSAX();
            String filePath = catalog + "\\file.xml";
            var eventslist = sax.readerSaxDocument(filePath);
            if (eventslist.size() > 0)
            {
                for (Eventlist eventlist : eventslist)
                {
                    calendarArea.appendText(eventlist.toString() + "\n");
                }
            }
        }

    }
@FXML
    public void DeleteId(javafx.event.ActionEvent actionEvent) throws IOException
    {
        if(choose_BD.isSelected()) {
            var mySqlObj = new ParseSQL();
            var deleteId = Integer.parseInt(id_TA.getText().trim());
            try {
                mySqlObj.deleteRecord(deleteId);
            } catch (SQLException throwables) {
                throwables.printStackTrace();
            }
        }
        else
        {
            var prop = new ParseProperties();
            var catalog = prop.readCatalogRoot();
            var sax = new ParseSAX();
            String filePath = catalog + "\\file.xml";
            SetData set = new SetData();
            var searchId = Integer.parseInt(id_TA.getText().trim());
            set.deleteEvent(filePath, searchId);
        }
    }

    @FXML
    public void ChangeAll(javafx.event.ActionEvent actionEvent) throws IOException
    {
        if(calendarArea != null)
        {
            calendarArea.clear();
        }
        var event_name = event_name_TA.getText();
        var event_type = event_type_CB.getSelectionModel().getSelectedItem().toString();
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd");
        LocalDate date_start_ta_pickValue = date_start_TA_pick.getValue();
        LocalDate date_end_ta_pickValue = date_end_TA_pick.getValue();
        var date_start =  date_start_ta_pickValue.format(formatter);
        var date_end = date_end_ta_pickValue.format(formatter);
        var manager =  manager_TA.getText();
        var place = place_TA.getText().trim();
        var searchId = Integer.parseInt(id_TA.getText().trim());

        if(choose_BD.isSelected())
        {
            var mySqlObj = new ParseSQL();
            try {
                mySqlObj.updateRecord(searchId,new Eventlist(searchId, event_name,event_type,date_start, date_end,
                        manager,place));
            } catch (SQLException throwables) {
                throwables.printStackTrace();
            }
            calendarArea.appendText("Запись № "+ searchId+" была успешно изменена в базе данных\n");
        }
        else
        {
            var prop = new ParseProperties();
            var catalog = prop.readCatalogRoot();
            String filePath = catalog + "\\file.xml";
            var sax = new ParseSAX();
            var events = sax.readerSaxDocument(filePath);
            boolean flag = false;
            for (int i = 0; i < events.size(); i++) {
                if (events.get(i).getId() == searchId)
                {
                    events.set(i, new Eventlist(searchId, event_name,event_type,date_start, date_end,
                            manager,place));
                    flag = true;
                    break;
                }
                if (flag) {
                    var dom = new ParseDOM(filePath);
                    dom.setDomNodes(events);
                    calendarArea.appendText("Запись № "+ searchId+" была успешно изменена в файле\n");
                } else {
                    System.out.println("Такого события нет!");
                }
            }
    }
}
@FXML
    public void FindID(javafx.event.ActionEvent actionEvent) throws IOException
    {
        if(calendarArea != null)
        {
            calendarArea.clear();
        }
        var searchId = id_TA.getText().trim();

        if (choose_BD.isSelected())
        {
            var mySqlObj = new ParseSQL();
            var search= Integer.parseInt(searchId);
             try {
                var result = mySqlObj.searchRecord(search);
                 while (result.next())
                 {
                     Eventlist eventlist = new Eventlist(
                             result.getInt("id"),
                             result.getString("event_name"),
                             result.getString("event_type"),
                             result.getString("date_start"),
                             result.getString("date_end"),
                             result.getString("manager"),
                             result.getString("place")
                     );
                     calendarArea.appendText(eventlist.toString() + "\n");
                     System.out.println(eventlist.toString());
                 }

            } catch (SQLException throwables) {
                throwables.printStackTrace();
            }
        }
        else
        {
            var sax = new ParseSAX();
            var prop = new ParseProperties();
            var catalog = prop.readCatalogRoot();
            String filePath = catalog + "\\file.xml";
            //String content = id_TA.getText();
            var event = sax.searchSaxDocument(filePath, searchId);
            calendarArea.setText("");
            calendarArea.appendText(event != null ? event.toString() : "Такого события нет!"+ "\n");
        }

    }
@FXML
    public void AddId(javafx.event.ActionEvent actionEvent) throws IOException
    {
        if(calendarArea != null)
        {
            calendarArea.clear();
        }
    var event_name = event_name_TA.getText();
    var event_type = event_type_CB.getSelectionModel().getSelectedItem().toString();

    DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd");
    LocalDate date_start_ta_pickValue = date_start_TA_pick.getValue();
    LocalDate date_end_ta_pickValue = date_end_TA_pick.getValue();

    var date_start = date_start_ta_pickValue.format(formatter);
    var date_end = date_end_ta_pickValue.format(formatter);

    var manager = manager_TA.getText();
    var place = place_TA.getText().trim();

    var searchId = Integer.parseInt(id_TA.getText().trim());
    if (choose_BD.isSelected()) {
        var mySqlObj = new ParseSQL();
        try {
            mySqlObj.addNewRecord(new Eventlist(searchId + 1, event_name, event_type, date_start, date_end, manager, place));
        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }
        calendarArea.appendText( "Запись была успешно записана в Базу данных!\n Нажмите кнопку 'ПРОСМОТР'");
    } else {
        SetData set = new SetData();
        var sax = new ParseSAX();

        var prop = new ParseProperties();
        var catalog = prop.readCatalogRoot();
        String filePath = catalog + "\\file.xml";

        var eventslist = sax.readerSaxDocument(filePath);
        var newEvent = set.setNewEvent(eventslist.size(), event_name, event_type, date_start, date_end, manager, place);
        eventslist.add(newEvent);

        var dom = new ParseDOM(filePath);
        dom.setDomNodes(eventslist);
        calendarArea.appendText( "Запись была успешно записана в файл!\n Нажмите кнопку 'ПРОСМОТР'");
    }


}

 @FXML
    public void ConvertXMLtoDB(javafx.event.ActionEvent actionEvent) throws IOException
    {
        var prop = new ParseProperties();
        var catalog = prop.readCatalogRoot();
        String filePath = catalog + "\\file.xml";
        var sax = new ParseSAX();
        var parsing = new Parse(sax.readerSaxDocument(filePath));
        parsing.parseXMLtoDB();
        if(calendarArea != null)
        {
            calendarArea.clear();
        }
        calendarArea.appendText( "Файл был успешно записан в базу данных!\n");
    }
    @FXML
    public void ConvertDBtoXML(javafx.event.ActionEvent actionEvent) throws IOException
    {
        ArrayList<Eventlist> eventslist = new ArrayList<Eventlist>();
        var prop = new ParseProperties();
        var catalog = prop.readCatalogRoot();
        String filePath = catalog + "\\file.xml";
        //var sax = new ParseSAX();
        var dom = new ParseDOM(filePath);
        var parsing = new Parse(eventslist,dom);
        parsing.parseDBtoXML();
        if(calendarArea != null)
        {
            calendarArea.clear();
        }
        calendarArea.appendText( "Данные были успешнно записаны в файл и доступны по адресу\n:"+filePath+"\n");
    }
}

