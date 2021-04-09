package sample;

import ru.bstu.it32.kurbatova.lab3.*;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import ru.bstu.it32.kurbatova.lab3.Main;

import java.util.ArrayList;

public class Controller {
    @FXML
    private TextField figureName;
    @FXML
    private Label label1;
    @FXML
    private Label label2;
    @FXML
    private Label label3;
    @FXML
    private TextField parametr1;
    @FXML
    private TextField parametr2;
    @FXML
    private TextField parametr3;
    @FXML
    private TextArea result;
    @FXML
    private Button btn1;
    @FXML
    private ComboBox FigureName;
    @FXML
    private Button btn;
    @FXML
    TreeView selectionTreeView;
    ArrayList<Figure.GeometricShapes> shapes = new ArrayList<>();

    public void createTree(String... rootItems) {
        //create root
        TreeItem rootFigure = new TreeItem("Фигуры");
        rootFigure.setExpanded(true);
        //create child
        TreeItem circle = new TreeItem("Круг");
        TreeItem triangle = new TreeItem("Треугольник");
        TreeItem rectangle = new TreeItem("Прямоугольник");

        rootFigure.getChildren().add(circle);
        rootFigure.getChildren().add(triangle);
        rootFigure.getChildren().add(rectangle);

        selectionTreeView.setRoot(rootFigure);
    }

    public void handleButtonExpand(javafx.event.ActionEvent actionEvent) {
        createTree();
    }
    public void handleComboBox(javafx.event.ActionEvent actionEvent)
    {
        String value = FigureName.getSelectionModel().getSelectedItem().toString();

        if (value == null || value.trim().equals(""))
        {
            this.writeMessage("Item cannot be empty.");
            return;
        }
        if(value.equals("Круг"))
        {
            parametr2.setVisible(false);
            label2.setVisible(false);
            parametr3.setVisible(false);
            label3.setVisible(false);
            label1.setText("Радиус");
            parametr1.setPromptText("Введите радиус");
        }
        else
        {
            if(value.equals("Прямоугольник"))
            {
                parametr3.setVisible(false);
                label3.setVisible(false);
                parametr2.setPromptText("Введите сторону b");
                parametr1.setPromptText("Введите сторону a");
                label1.setText("Сторона a");
                label2.setText("Сторона b");
            }
            else
            {
                if(value.equals("Треугольник"))
                {
                    parametr2.setVisible(true);
                    label2.setVisible(true);
                    parametr3.setVisible(true);
                    label3.setVisible(true);

                    parametr3.setPromptText("Введите сторону c");
                    parametr2.setPromptText("Введите сторону b");
                    parametr1.setPromptText("Введите сторону a");
                    label1.setText("Сторона a");
                    label2.setText("Сторона b");
                    label3.setText("Сторона c");
                }
            }

        }
    }
    public void handleResult(javafx.event.ActionEvent actionEvent)
    {
        int max = 0;
        result.setText(shapes.get(Main.GetMax(shapes,max)).toString());
    }
    public void handleButtonAdd(javafx.event.ActionEvent actionEvent)
    {

        String value = FigureName.getSelectionModel().getSelectedItem().toString();
        String result;
        if (value == null || value.trim().equals(""))
        {
            this.writeMessage("Item cannot be empty.");
            return;
        }
        else {
            switch (value) {
                case "Треугольник":
                    result = parametr1.getText()+ ","+parametr2.getText()+ ","+parametr3.getText()+ ","+ value;
                    Triangle triangle = new Triangle();
                    triangle.init(result);
                    shapes.add(triangle);
                    break;
                case "Круг":
                    result = parametr1.getText()+ ","+ value;
                    Circle circle = new Circle();
                    circle.init(result);
                    shapes.add(circle);
                    break;
                case "Прямоугольник":
                    result = parametr1.getText()+ ","+parametr2.getText()+","+ value;
                    Rectangle rectangle = new Rectangle();
                    rectangle.init(result);
                    shapes.add(rectangle);
                    break;
                default:
                    throw new IllegalStateException("Unexpected value: " + value);
            }
        }
        addItem(figureName.getText());
    }

    private void addItem(String value)
    {
        if (value == null || value.trim().equals(""))
        {
            this.writeMessage("Item cannot be empty.");
            return;
        }
        String root = FigureName.getSelectionModel().getSelectedItem().toString();
//        TreeItem<String> parent = new TreeItem(root);

       TreeItem<String> parent = (TreeItem<String>) selectionTreeView.getSelectionModel().getSelectedItem();

        if (parent == null)
        {
            this.writeMessage("Select a node to add this item to.");
            return;
        }

        // Check for duplicate
        for(TreeItem child : parent.getChildren())
        {

            if (child.getValue().equals(value))
            {
                this.writeMessage(value + " already exists under " + parent.getValue());
                return;
            }
        }

        TreeItem newItem = new TreeItem(value);
        parent.getChildren().add(newItem);

        if (!parent.isExpanded())
        {
            parent.setExpanded(true);
        }
    }


    private void writeMessage(String s) {
    }
}
