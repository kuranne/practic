import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class trilk {
    private static FastInput in = new FastInput(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));

    public static void main(String[] args) {
        Trick glass = new Trick(1);
        String cmd = in.next().trim();

        for (char c: cmd.toCharArray()) {
            switch (c) {
                case 'A':
                    glass.sf();
                    break;
                case 'B':
                    glass.ss();
                    break;
                case 'C':
                    glass.st();
                default:
                    break;
            }
        }

        if (glass.f) {out.println(1);}
        else if (glass.s) {out.println(2);}
        else {out.println(3);}

        out.flush();
    }

    static class Trick {
        boolean f = false;
        boolean s = false;
        boolean t = false;
        boolean tmp;

        public Trick(int init) {
            switch (init) {
                case 1:
                    f = true;
                    break;
                case 2:
                    s = true;
                    break;
                case 3:
                    t = true;
                default:
                    break;
            }
        }

        public void sf() {
            tmp = f;
            f = s;
            s = tmp;
        }

        public void ss() {
            tmp = s;
            s = t;
            t = tmp;
        }

        public void st() {
            tmp = f;
            f = t;
            t = tmp;
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
