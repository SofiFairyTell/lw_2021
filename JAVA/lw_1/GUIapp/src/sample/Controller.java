package sample;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.input.MouseEvent;
import javafx.scene.shape.Polygon;
import ru.bstu.it32.kurbatova.lab1.*;

public class Controller
{
    @FXML
    private TextArea result_mark;
    @FXML
    private TextField mark;
    @FXML
    private TextField radius;
    @FXML
    private TextField length;
    @FXML
    private TextArea result_TrInCir;
    @FXML
    private Button btn;

    @FXML
    public void initialize(){
        btn.addEventHandler(MouseEvent.MOUSE_CLICKED, new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent mouseEvent) {
                btn.setText("Thanks!");
            }
        });
    }
    @FXML
    private void isTriangleInCircle_click(ActionEvent event)
    {
        int len = Integer.parseInt(length.getText());
        int rad = Integer.parseInt(radius.getText());
        result_TrInCir.setText(ComputeMethod.isTriangleInCircle(rad,len));
    }
    @FXML
    private void markTranslator_click(ActionEvent actionEvent)
    {
        int mark_i = Integer.parseInt(mark.getText());
        result_mark.setText(ComputeMethod.markTranslator(mark_i));
    }
}
