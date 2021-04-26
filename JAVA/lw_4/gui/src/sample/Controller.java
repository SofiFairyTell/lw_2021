package sample;

import ru.bstu.it32.kurbatova.lab4.*;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.web.HTMLEditor;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

public class Controller
{
    @FXML
    private TextField textParam;
    @FXML
    private HTMLEditor htmlEdit;
    @FXML
    private Button btn;

    public void EditHtml(javafx.event.ActionEvent actionEvent) throws IOException {
        String value = textParam.getText();
        Parametres param = new Parametres();
        param.Parametres(value);
        String replacemenet = " width = '" + param.Width() + "' height = '" + param.Height() + "'";
        //Соберем из созданного файла новый файл
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter("result.html"));
        bufferedWriter.write(htmlEdit.getHtmlText());
        bufferedWriter.close();

    }
}
