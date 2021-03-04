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
import java.text.MessageFormat;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.logging.Level;

public class Controller
{
    @FXML
    private TextArea summ_result;
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
    private  TextField array;
    @FXML
    private TextArea result_TrInCir;
    @FXML
    private Button btn;
    @FXML
    private Button btn_mark;
    public Button btn_tri;

    @FXML
    public void initialize()
        {
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
            if (length.getText().equals("") || radius.getText().equals("")) return;
            int len = Integer.parseInt(length.getText());
            int rad = Integer.parseInt(radius.getText());
            String msg, res;
            res = ComputeMethod.isTriangleInCircle(rad,len);
            msg = MessageFormat.format("Введено:{0} {1}. Возвращено: {2}", len, rad, res);
            Main.logs.log(Level.FINE,msg+res);
            result_TrInCir.setText(res);
        }
    @FXML
    private void markTranslator_click(ActionEvent actionEvent)
        {
            if (mark.getText().equals("")) return;
            int mark_i = Integer.parseInt(mark.getText());
            result_mark.setText(ComputeMethod.markTranslator(mark_i));
        }
    @FXML
    private void TrigonometryFunction_click(ActionEvent actionEvent)
        {
            if (start.getText().equals("") || end.getText().equals("")|| step.getText().equals("")) return;
            int start_i = Integer.parseInt(start.getText());
            int end_i = Integer.parseInt(end.getText());
            int step_i = Integer.parseInt(step.getText());
            double[][] array = ComputeMethod.TrigonometryFunction(start_i,end_i,step_i);
            for(int i = 0; i < array.length; ++i)
                table_result.appendText(String.format("%-10.2f%-27.2f%n", array[i][0], array[i][1]));
        }
    @FXML
    private void ArraySum_click(ActionEvent actionEvent)
        {
            if (array.getText().equals("")) return;
            String[] arr = array.getText().split(",");
            int[] arr_int = new int[arr.length];
            for (int i = 0; i<arr.length; i++)
            {
                arr_int[i] = Integer.parseInt(arr[i]);
            }

            summ_result.setText(ComputeMethod.ArraySum(arr_int));
        }
    }