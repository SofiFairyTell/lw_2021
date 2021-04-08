package sample;

import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TreeItem;
import javafx.scene.control.TreeView;

import java.awt.event.ActionEvent;

public class Controller {
    @FXML
    private Button btn;
    @FXML
    TreeView selectionTreeView;
    @FXML
    private void handleButtonAction(ActionEvent event) {
        createTree();
    }

    public void createTree(String... rootItems) {
        //create root
        TreeItem rootFigure = new TreeItem("Фигуры");
        rootFigure.setExpanded(true);
        //create child
        TreeItem<String> circle = new TreeItem("Круг");
        TreeItem<String> triangle = new TreeItem("Треугольник");
        TreeItem<String> rectangle = new TreeItem("Прямоугольник");
//        temChild.setExpanded(true);

        rootFigure.getChildren().add(circle);
        rootFigure.getChildren().add(triangle);
        rootFigure.getChildren().add(rectangle);

        selectionTreeView.setRoot(rootFigure);
    }

    public void handleButtonAction(javafx.event.ActionEvent actionEvent) {
        createTree();
    }
    
}
