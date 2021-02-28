package sample;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.input.MouseEvent;
import javafx.scene.shape.Polygon;
import ru.bstu.it32.kurbatova.lab1.*;

import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Controller
{

    @FXML
    private TableView<ObservableList<Double>> table;
    @FXML
    private TableColumn<Double,Double> column;
    @FXML
    private  TableColumn<Double,Double> column1;
    @FXML
    private TextField start;
    @FXML
    private TextField end;
    @FXML
    private TextField step;
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
    private Button btn_mark;
    public Button btn_tri;

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
    @FXML
    private void TrigonometryFunction_click(ActionEvent actionEvent)
    {
        int start_i = Integer.parseInt(start.getText());
        int end_i = Integer.parseInt(end.getText());
        int step_i = Integer.parseInt(step.getText());
        double[][] array = ComputeMethod.TrigonometryFunction(start_i,end_i,step_i);

    ObservableList<Double>
        TableColumn x = new TableColumn("X");
        TableColumn y = new TableColumn("Y");
        table.getColumns().addAll(x,y);
        table.setItems();



    }
}
