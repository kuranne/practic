import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class WordChain {
    public static void main(String[] args) {
        int len = in.nextInt();
        String prev = new String();
        int n = in.nextInt();
        outer: for (int i = 0; i < n; i++) {
            if (i == 0) {
                prev = in.next();
                continue;
            }
            String curr = in.next();
            int count = 0;
            for (int j = 0; j < len; j++) {
                if (curr.charAt(j) != prev.charAt(j)) {count++;}
                if (count > 2) break outer;
            }
            prev = curr;
        }
        out.println(prev);
        out.flush();
    }
    
    private static final PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
    private static final FastReader in = new FastReader(System.in);
    private static class FastReader {
        private static BufferedReader br;
        private static StringTokenizer stt;


        public FastReader(InputStream in) {
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

        public int nextInt() {
            return Integer.parseInt(next());
        }
    }   
}