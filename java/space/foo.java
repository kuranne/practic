
import java.io.BufferedOutputStream;
import java.io.DataInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;

public class foo {
    private static final PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out), true);
    private static final FastReader in = new FastReader(System.in);
    public static void main(String[] args) {
        try {
            out.println(in.nextLong() + in.nextLong());
        } catch (IOException l) {
            throw new RuntimeException(l);
        }
    }   

    private static class FastReader {
        private final int BUF_SIZE = 1 << 16;
        private final DataInputStream din;
        private final byte[] buf;
        private int bufPointer, bytesRead;

        public FastReader(InputStream in) {
            din = new DataInputStream(in);
            buf = new byte[BUF_SIZE];
            bufPointer = bytesRead = 0;
        }

        public long nextLong() throws IOException {
            long ret = 0;
            byte c = read();
            while (c <= ' ') c = read();

            boolean neg = c == '-';
            if (neg) c = read();

            do {
                ret = ret * 10 + (c - '0');
            } while ((c = read()) >= '0' && c <= '9');
            return (neg) ? -ret : ret;
        }

        private byte read() throws IOException {
            if (bytesRead == bufPointer) fillBuf();
            return buf[bufPointer++];
        }

        private void fillBuf() throws IOException {
            bytesRead = din.read(buf, bufPointer = 0, BUF_SIZE);
            if (bytesRead == 0) bytesRead = -1;
        }        
    }
}
