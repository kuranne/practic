import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.Collections;
import java.util.StringTokenizer;
import java.util.Vector;

public class abc {
    private static FastInput in = new FastInput(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));

    public static void main(String[] args) {
        Vector<Pair> abc = new Vector<>();
        Vector<Integer> nums = in.nextLineInt();
        Collections.sort(nums);

        char[] c = in.nextLine().toCharArray();

        for (int i = 0; i < nums.size(); i++) {
            abc.add(new Pair(nums.get(i), (char)('A' + i) ));
        }

        for (char x: c) {
            for (Pair p: abc) {
                if (x == p.c) {
                    out.printf("%d ", p.n);
                }
            }
        }

        out.println();
        out.flush();
    }

    static class Pair {
        int n;
        char c;

        public Pair(int num, char ch) {
            n = num;
            c = ch;
        }
    }

    static class FastInput {
        BufferedReader br;
        StringTokenizer stt;

        public FastInput(InputStream in) {
            br = new BufferedReader(new InputStreamReader(in));
            stt = new StringTokenizer("");
        }

        public String nextLine() {
            try {
                return br.readLine();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        public Vector<Integer> nextLineInt() {
            Vector<Integer> vec = new Vector<>();

            String line = nextLine();
            if (line.isEmpty() || line == null) {
                return vec;
            }

            stt = new StringTokenizer(line);

            while (stt.hasMoreTokens()) {
                try {
                    vec.add(Integer.parseInt(stt.nextToken()));
                } catch (NumberFormatException e) {
                    throw new RuntimeException(e);
                }
            }

            return vec;
        }
    }
}