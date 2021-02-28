package sample;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.shape.Polygon;
import ru.bstu.it32.kurbatova.lab1.*;

public class Controller
{
    @FXML
    private TextField radius;
    @FXML
    private TextField length;
    @FXML
    private TextArea textArea;
    @FXML
    private Button btn;
    @FXML
    private void click(ActionEvent event)
    {
        btn.setText("You've clicked!");
        int len = Integer.parseInt(length.getText());
        int rad = Integer.parseInt(radius.getText());
        ComputeMethod t;
        t = new ComputeMethod();
        textArea.setText(ComputeMethod.isTriangleInCircle(len,rad));

    }
}
