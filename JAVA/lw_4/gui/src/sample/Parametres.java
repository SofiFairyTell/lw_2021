package sample;

import java.util.Scanner;

public class Parametres {
    private  int width;
    private int height;

    public  void Parametres( Scanner scanner)
    {
        this.width = scanner.nextInt();
        this.height = scanner.nextInt();
    }

    public void Parametres(String string)
    {
        String[] arr = string.split(",");
        this.width = Integer.parseInt(arr[0]);
        this.height = Integer.parseInt(arr[1]);
    }

    public int Width()
    {
        return width;
    }

    public int Height()
    {
        return height;
    }
}
