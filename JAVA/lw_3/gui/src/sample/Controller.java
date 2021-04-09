package sample;

import javafx.fxml.FXML;
import javafx.scene.control.*;

import java.awt.event.ActionEvent;

public class Controller {
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

    public void handleButtonAdd(javafx.event.ActionEvent actionEvent)
    {
        addItem(FigureName.getSelectionModel().getSelectedItem().toString());
    }

    private void addItem(String value)
    {
        if (value == null || value.trim().equals(""))
        {
            this.writeMessage("Item cannot be empty.");
            return;
        }

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
