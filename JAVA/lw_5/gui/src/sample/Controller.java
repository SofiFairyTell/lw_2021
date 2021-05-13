package sample;

import javafx.fxml.FXML;
import javafx.scene.control.ComboBox;
import javafx.scene.control.DatePicker;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import ru.bstu.it32.kurbatova.lab5.*;

import java.io.IOException;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;

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
    public void WatchAll(javafx.event.ActionEvent actionEvent) throws IOException {
        if(calendarArea != null)
        {
            calendarArea.clear();
        }
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
@FXML
    public void DeleteId(javafx.event.ActionEvent actionEvent) throws IOException
    {
        var prop = new ParseProperties();
        var catalog = prop.readCatalogRoot();
        var sax = new ParseSAX();
        String filePath = catalog + "\\file.xml";
        SetData set = new SetData();
        var searchId = Integer.parseInt(id_TA.getText().trim());
        set.deleteEvent(filePath,searchId);
    }
@FXML
    public void ChangeAll(javafx.event.ActionEvent actionEvent) throws IOException {
        SetData set = new SetData();
        var prop = new ParseProperties();
        var catalog = prop.readCatalogRoot();
        String filePath = catalog + "\\file.xml";
        var sax = new ParseSAX();
        var events = sax.readerSaxDocument(filePath);

        //event_name_TA.setText("Встреча");

        var event_name = event_name_TA.getText();
        var event_type = event_type_CB.getSelectionModel().getSelectedItem().toString();

        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd LLLL yyyy");
        LocalDate date_start_ta_pickValue = date_start_TA_pick.getValue();
        LocalDate date_end_ta_pickValue = date_end_TA_pick.getValue();

        var date_start =  date_start_ta_pickValue.format(formatter);
        var date_end = date_end_ta_pickValue.format(formatter);


        var manager =  manager_TA.getText();
        var place = place_TA.getText().trim();
        var searchId = Integer.parseInt(id_TA.getText().trim());
        boolean flag = false;
        for (int i = 0; i < events.size(); i++) {
            if (events.get(i).getId() == searchId) {
                events.set(i, new Eventlist(searchId, event_name,event_type,date_start, date_end,
                       manager,place));
                flag = true;
                break;
            }
    }
    if (flag) {
        var dom = new ParseDOM(filePath);
        dom.setDomNodes(events);
    } else {

        System.out.println("Такого события нет!");
    }
}
@FXML
    public void FindID(javafx.event.ActionEvent actionEvent) throws IOException
    {
        var sax = new ParseSAX();
        var prop = new ParseProperties();
        var catalog = prop.readCatalogRoot();
        String filePath = catalog + "\\file.xml";
        String content = id_TA.getText();
        var event = sax.searchSaxDocument(filePath, content);
        calendarArea.setText("");
        calendarArea.appendText(event != null ? event.toString() : "Такого события нет!"+ "\n");
    }
@FXML
    public void AddId(javafx.event.ActionEvent actionEvent) throws IOException
    {
        SetData set = new SetData();
        var sax = new ParseSAX();

        var prop = new ParseProperties();
        var catalog = prop.readCatalogRoot();
        String filePath = catalog + "\\file.xml";

        var eventslist = sax.readerSaxDocument(filePath);

        var event_name = event_name_TA.getText();
        var event_type = event_type_CB.getSelectionModel().getSelectedItem().toString();

        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd LLLL yyyy");
        LocalDate date_start_ta_pickValue = date_start_TA_pick.getValue();
        LocalDate date_end_ta_pickValue = date_end_TA_pick.getValue();

        var date_start =  date_start_ta_pickValue.format(formatter);
        var date_end = date_end_ta_pickValue.format(formatter);

        var manager =  manager_TA.getText();
        var place = place_TA.getText().trim();

        var newEvent = set.setNewEvent(eventslist.size(), event_name,event_type,date_start, date_end, manager,place);
        eventslist.add(newEvent);

        var dom = new ParseDOM(filePath);
        dom.setDomNodes(eventslist);
    }
 @FXML
    public void ConvertXMLtoBD()(javafx.event.ActionEvent actionEvent) throws IOException
    {

    }
    @FXML
    public void ConvertBDtoXML()(javafx.event.ActionEvent actionEvent) throws IOException
    {

    }
}

