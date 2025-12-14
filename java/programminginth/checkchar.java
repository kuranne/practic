import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class checkchar {
    private static FastInput in = new FastInput(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
    public static void main(String[] args) {
        String txt = in.next().trim();
        downAndUpCheck du = new downAndUpCheck(false, false);
        txt.chars().mapToObj(c -> (char) c)
            .forEach(c -> {
                if (c >= 'A' && c <= 'Z') {du.up = true;}
                else {du.down = true;}
            });
        if (du.up && du.down) {
            out.println("Mix");
        } else if (du.up) {
            out.println("All Capital Letter");
        } else {
            out.println("All Small Letter");
        }
        out.flush();
    }

    static class downAndUpCheck {
        boolean down;
        boolean up;
        public downAndUpCheck(boolean d, boolean u) {
            boolean down = d;
            boolean up = u;
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
    }
}
