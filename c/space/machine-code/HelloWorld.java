import java.io.BufferedOutputStream;
import java.io.PrintWriter;

public class HelloWorld {
    private static final PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
    public static void main(String[] args) {
        out.println("Hello World!");
        out.flush();
    }
}