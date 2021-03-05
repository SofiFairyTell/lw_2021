package guiapp;

import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.input.MouseEvent;
import java.text.MessageFormat;
import java.util.logging.Level;
import ru.bstu.it32.kurbatova.lab1.*;

public class Controller {
    @FXML
    private TextArea summ_result;
    @FXML
    private TextArea table_result;
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
    private TextField array;
    @FXML
    private TextArea result_TrInCir;
    @FXML
    private Button btn;
    @FXML
    private Button btn_tri;

/**
 * <p> Инициализация</p>
 * При нажатии на кнопку на первой вкладке на ней появляется надпись
 * */
    @FXML
    public void initialize() {
        btn.addEventHandler(MouseEvent.MOUSE_CLICKED, new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent mouseEvent) {
                btn.setText("Thanks!");
            }
        });
    }

    /**
     * <p>Описание метода isTriangleInCircle_click</p>
     *  len длина стороны целое число
     *  rad радиус круг целое число
     *  return добавление текста в TextArea result_TrInCir
     * */
    @FXML
    public void isTriangleInCircle_click(ActionEvent event) {
        if (length.getText().equals("") || radius.getText().equals("")) {
            Main.logs.log(Level.INFO, "Передана пустая строка");
            return;
        }
        try {
            int len = Integer.parseInt(length.getText());
            int rad = Integer.parseInt(radius.getText());
            String msg, res;
            res = ComputeMethod.isTriangleInCircle(rad, len);
            msg = MessageFormat.format("Введено:{0} {1}. Возвращено: {2}", len, rad, res);
            Main.logs.log(Level.FINE, msg + res);
            result_TrInCir.setText(res);
        } catch (ArithmeticException e) {
            Main.logs.log(Level.SEVERE, e.getMessage());
        }
    }

    /**
     * <p>Описание метода markTranslator_click</p>
     *  mark  оценка целое число
     *  return добавление текста в TextArea result_mark
     * */
    @FXML
    public void markTranslator_click(ActionEvent actionEvent) {
        if (mark.getText().equals("")) {
            Main.logs.log(Level.INFO, "Передана пустая строка");
            return;
        }
        int mark_i = Integer.parseInt(mark.getText());
        result_mark.setText(ComputeMethod.markTranslator(mark_i));
        Main.logs.log(Level.FINE, "Метод успешно выполнен");
    }

    /**
     * <p>Описание метода TrigonometryFunction_click</p>
     *  start  начальная точка целое число
     *  end конечная точка целое число
     *  step шаг целое число
     *  return добавление текста в TextArea table_result
     * */
    @FXML
    public void TrigonometryFunction_click(ActionEvent actionEvent) throws Exception {
        if (start.getText().equals("") || end.getText().equals("") || step.getText().equals("")) {
            Main.logs.log(Level.INFO, "Передана пустая строка");
            return;
        }
        try {
            int start_i = Integer.parseInt(start.getText());
            int end_i = Integer.parseInt(end.getText());
            int step_i = Integer.parseInt(step.getText());
            double[][] array = ComputeMethod.TrigonometryFunction(start_i, end_i, step_i);
            for (int i = 0; i < array.length; ++i)
                table_result.appendText(String.format("%-10.2f%-27.2f%n", array[i][0], array[i][1]));
            Main.logs.log(Level.FINE, "Метод успешно выполнен");
        } catch (ArithmeticException e) {
            Main.logs.log(Level.SEVERE, e.getMessage());
        }
    }

    /**
     * <p>Описание метода ArraySum_click</p>
     *  arr_int последовательность чисел целое число
     *  return добавление текста в TextArea summ_result
     * */
    @FXML
    public void ArraySum_click(ActionEvent actionEvent) {
        if (array.getText().equals("")) return;
        try {
            String[] arr = array.getText().split(",");
            int[] arr_int = new int[arr.length];
            for (int i = 0; i < arr.length; i++) {
                arr_int[i] = Integer.parseInt(arr[i]);
            }
            summ_result.setText(ComputeMethod.ArraySum(arr_int));
            Main.logs.log(Level.FINE, "Метод успешно выполнен");
        } catch (ArithmeticException e) {
            Main.logs.log(Level.SEVERE, e.getMessage());
        }
    }
}