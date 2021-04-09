package sample;

import javafx.beans.value.ObservableValue;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.*;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

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


    public void createTree(String... rootItems) {
        //create root
        TreeItem rootFigure = new TreeItem("Фигуры");
        rootFigure.setExpanded(true);
        //create child
        TreeItem<String> circle = new TreeItem("Круг");
        TreeItem<String> triangle = new TreeItem("Треугольник");
        TreeItem<String> rectangle = new TreeItem("Прямоугольник");

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
        selectionTreeView.getSelectionModel().setSelectionMode();
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
    public void handleButtonAdd(javafx.event.ActionEvent actionEvent)
    {
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
