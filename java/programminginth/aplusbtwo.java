import java.util.*;
import java.io.*;

public class aplusbtwo {
    private static FastInput in = new FastInput(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));

    public static void main(String[] args) {
        int a = in.nextInt();
        int b = in.nextInt();

        out.println(a + b);
        out.flush();
    }

    static class FastInput {
        BufferedReader br;
        StringTokenizer stk;

        public FastInput(InputStream in) {
            br = new BufferedReader(new InputStreamReader(in));
            stk = new StringTokenizer("");
        }

        public String next() {
            while (!stk.hasMoreTokens()) {
                try {
                    stk = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
            return stk.nextToken();
        }

        public int nextInt() {
            return Integer.parseInt(next());
        }

        public long nextLong() {
            return Long.parseLong(next());
        }

        public double nextDouble() {
            return Double.parseDouble(next());
        }
    }
}