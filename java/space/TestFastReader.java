import func.io.FastReader;
import java.io.BufferedOutputStream;
import java.io.IOException;
import java.io.PrintWriter;

public class TestFastReader {
    private static final FastReader in = new FastReader(System.in);
    private static final PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out), true);
    public static void main(String[] args) throws IOException {
        out.println(in.next());
        out.println(in.nextInt());
        out.println(in.nextDouble());
    }
}
