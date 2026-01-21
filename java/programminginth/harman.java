import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class harman {
    private static FastInput in = new FastInput(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
    public static void main(String[] args) {
        Herman x = new Herman(in.nextDouble());
        out.printf("%.6f\n%.6f\n", x.euclideanArea(), x.taxiArea());
        out.flush();
    }

    static class Herman {
        double r;
        double PI = Math.PI;

        public Herman(double radius) {
            r = radius;
            r *= r;
        }

        public double euclideanArea() {
            return PI * r;
        }

        public double taxiArea() {
            return 2 * r;
        }
    }

    static class FastInput {
        BufferedReader br;
        StringTokenizer stt;

        public FastInput(InputStream in) {
            br = new BufferedReader(new InputStreamReader(in));
            stt = new StringTokenizer("");
        }

        public String next() {
            while (!stt.hasMoreTokens()) {
                try {
                    stt = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
            return stt.nextToken();
        }

        public double nextDouble() {
            return Double.parseDouble(next());
        }
    }
}
