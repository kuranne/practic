package func.io;

import java.io.DataInputStream;
import java.io.IOException;
import java.io.InputStream;

public class FastReader {
    private final int BUFFER_SIZE = 1 << 16;
    private final DataInputStream din;
    private final byte[] buf;
    private int bufPointer, bytesRead;

    public FastReader(InputStream in) {
        din = new DataInputStream(in);
        buf = new byte[BUFFER_SIZE];
        bufPointer = bytesRead = 0;
    }

    public String next() throws IOException {
        byte[] buffer = new byte[64];
        int cnt = 0;
        byte c = read();
        while (c <= ' ') c = read();
        do { 
            buffer[cnt++] = c;
        } while ((c = read()) > ' ');
        return new String(buffer, 0, cnt);
    }

    public int nextInt() throws IOException {
        int ret = 0;
        byte c = read();
        while (c <= ' ') c = read();
        
        boolean neg = c == '-';
        if (neg) c = read();

        do { 
            ret = ret * 10 + (c - '0');
        } while ((c = read()) >= '0' && c <= '9');

        return (neg) ? -ret : ret;
    }

    public double nextDouble() throws IOException {
        double ret = 0.0, mul = 1;
        byte c = read();
        while (c <= ' ') c = read();

        boolean neg = (c == '-');
        if (neg) c = read();

        do {
            ret = ret * 10 + (c - '0');
        } while ((c = read()) >= '0' && c <= '9');

        if (c == '.') {
            c = read();
            do { 
                ret += (c - '0') / (mul *= 10);
            } while ((c = read()) >= '0' && c <= '9');
        }
        return (neg) ? -ret : ret;
    }

    private byte read() throws IOException {
        if (bufPointer == bytesRead) fillBuf();
        return buf[bufPointer++];
    }

    private void fillBuf() throws IOException {
        bytesRead = din.read(buf, bufPointer = 0 ,BUFFER_SIZE);
        if (bytesRead == 0) buf[0] = -1;
    }
    
}