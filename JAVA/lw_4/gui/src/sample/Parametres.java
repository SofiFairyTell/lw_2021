package sample;

import java.util.Scanner;

public class Parametres {
    private double width;
    private double height;

    public Parametres() {
    }

    public void Parametres(Scanner scanner) {
        this.width = scanner.nextDouble();
        this.height = scanner.nextDouble();
    }

    public void Parametres(String string) {
        String[] arr = string.split(",");
        this.width = Double.parseDouble(arr[0]);
        this.height = Double.parseDouble(arr[1]);
    }

    public double Width() {
        return this.width;
    }

    public double Height() {
        return this.height;
    }
}
