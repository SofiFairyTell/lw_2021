package guiapp;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import java.util.logging.Logger;

import ru.bstu.it32.kurbatova.lab1.*;
public class Main extends Application {

    public static Logger logs = LoggerClass.setLog("logger_app");
    @Override
    public void start(Stage primaryStage) throws Exception{
        Parent root = FXMLLoader.load(getClass().getResource("g.fxml"));
        primaryStage.setTitle("LW_1");
        primaryStage.setScene(new Scene(root, 700, 600));
        primaryStage.show();
    }


    public static void main(String[] args) {
        launch(args);
    }

}
