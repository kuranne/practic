import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.Collections;
import java.util.StringTokenizer;
import java.util.Vector;

public class findMedian {
    private static FastInput in = new FastInput(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));

    public static void main(String[] args) {
        Median vec = new Median(in.nextLineInt());
        out.println(vec.median());
    }

    static class Median {
        Vector<Integer> ques;

        public Median(Vector<Integer> vec) {
            ques = vec;
            Collections.sort(ques);
        }

        public int median() {
            return ques.get(1);
        }
    }

    static class FastInput {
        BufferedReader br;

        public FastInput(InputStream in) {
            br = new BufferedReader(new InputStreamReader(in));
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
            StringTokenizer stt = new StringTokenizer(nextLine());

            while (stt.hasMoreTokens()) {
                vec.add(Integer.parseInt(stt.nextToken()));
            }

            return vec;
        }
    }
}
