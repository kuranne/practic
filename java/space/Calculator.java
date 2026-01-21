
import java.io.BufferedOutputStream;
import java.io.PrintWriter;

public class Calculator {
    private static PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));

    public static void main(String[] args) {
        out.println(new Calculate<Double>().multi(3.0, 4.0));
        out.flush();
    }
}