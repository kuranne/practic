import java.io.BufferedOutputStream;
import java.io.PrintWriter;
import java.util.*;

public class aplusb {
    private static Scanner in = new Scanner(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
    public static void main(String[] args) {
        int a = in.nextInt();
        int b = in.nextInt();

        out.println(a + b);
        out.flush();
    }
}