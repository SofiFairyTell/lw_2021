package sample;

import javafx.fxml.FXML;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import ru.bstu.it32.kurbatova.lab5.Eventlist;
import ru.bstu.it32.kurbatova.lab5.ParseProperties;
import ru.bstu.it32.kurbatova.lab5.ParseSAX;

import java.io.IOException;

public class Controller
{



    @FXML
    private TextField event_name_TA;
    @FXML
    private TextField date_start_TA;
    @FXML
    private TextField date_end_TA;
    @FXML
    private TextField manager_TA;
    @FXML
    private TextField place_TA;
    @FXML
    private TextArea calendarArea;
    @FXML
    private  TextField id_TA;
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

    }
@FXML
    public void  ChangeAll(javafx.event.ActionEvent actionEvent) throws IOException {
}
@FXML
    public  void FindID(javafx.event.ActionEvent actionEvent) throws IOException
    {
        var prop = new ParseProperties();
        var catalog = prop.readCatalogRoot();
        var sax = new ParseSAX();
        String filePath = catalog + "\\file.xml";
        String content = id_TA.getText();
        var event = sax.searchSaxDocument(filePath, content);
        calendarArea.setText("");
        calendarArea.appendText(event != null ? event.toString() : "Такого события нет!"+ "\n");
    }
@FXML
    public void AddId(javafx.event.ActionEvent actionEvent) throws IOException
{

}
}

