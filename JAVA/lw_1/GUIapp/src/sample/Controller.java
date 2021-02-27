package sample;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.shape.Polygon;


public class Controller
{
    @FXML
    private TextField textField;
    @FXML
    private TextArea textArea;
    @FXML
    private Button btn;
    @FXML
    private void click(ActionEvent event)
    {
        btn.setText("You've clicked!");
        String text = textField.getText();
        textArea.setText(text);

    }
}
