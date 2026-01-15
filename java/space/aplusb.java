import func.io.FastInput;
import java.io.BufferedOutputStream;
import java.io.PrintWriter;

public class AplusB {
    private static final FastInput in = new FastInput(System.in);
    private static final PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));

    public static void main(String[] args) {
        out.printf("\na: ");
        out.flush();

        int a = in.nextInt();

        out.printf("\nb: ");
        out.flush();

        int b = in.nextInt();

        out.printf("\na + b = %d\n", a + b);
        out.flush();
    }
}