package sample;
import javafx.beans.property.SimpleDoubleProperty;
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
    private TableView<double[]> table;
    @FXML
    private TextArea table_result;
    @FXML
    private double column;
    @FXML
    private double column1;
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
        //            table_result.setText(String.valueOf(array[i][0]));
        ////            String.valueOf(array[i][1]);
        for(int i = 0; i < array.length; ++i)
            table_result.appendText(String.format("%-10.2f%-27.2f%n", array[i][0], array[i][1]));
    }

    }