package sample;

import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;

import java.io.*;

public class Controller
{
    @FXML
    private TextField textParam;
    @FXML
    private TextArea htmlEdit;
    @FXML
    private TextArea htmlEdit1;
    @FXML
    private Button btn;
@FXML
    public void EditHtml(javafx.event.ActionEvent actionEvent) throws IOException {
        String value = textParam.getText();
        Parametres param = new Parametres();
        param.Parametres(value);
        String replacemenet = " width = '" + param.Width() + "' height = '" + param.Height() + "'";
        String filePath = "C:\\Users\\Kurbatova\\source\\LW2021\\JAVA\\lw_4\\src\\prj\\zad2.html";
    //Соберем из созданного файла новый файл
        BufferedReader bufferedReader = new BufferedReader(new FileReader(filePath));
        String str = "";


        while ((str = bufferedReader.readLine()) != null)
         {
             htmlEdit.appendText(str+'\n');
         }
        Parser parser = new Parser();
        parser.HtmlParser(filePath,replacemenet);

        BufferedReader bufferReader = new BufferedReader(new FileReader("result.html"));
        String after = "";
        while ((after = bufferReader.readLine()) != null)
        {
            htmlEdit1.appendText(after+'\n');
        }
    }

}

