import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class pythagorus {
    private static FastInput in = new FastInput(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));

    public static void main(String[] args) {
        Triangle x = new Triangle(in.nextDouble(), in.nextDouble());
        out.printf("%.6f\n", x.computeC());
        out.flush();
    }

    static class Triangle {
        double a;
        double b;
        double c;

        public Triangle(double ai, double bi) {
            a = ai;
            b = bi;
        }

        public double computeC() {
            c = Math.sqrt(
                Math.pow(a, 2) + Math.pow(b, 2)
            );
            return c;
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
