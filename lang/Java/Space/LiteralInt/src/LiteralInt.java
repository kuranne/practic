
import java.io.BufferedOutputStream;
import java.io.PrintWriter;

public class LiteralInt {
    private static final PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
    public static void main(String[] args) {
        int dicimal = 256;
        int binary = 0b0001_0000_0000;
        int octimal = 0400;
        int base16 = 0x100;

        out.printf("%d %d %d %d\n", dicimal, binary, octimal, base16);
        out.flush();
    }
}
