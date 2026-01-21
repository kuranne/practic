import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class minmax {
    private static FastInput in = new FastInput(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
    
    static class MandM {
        int min;
        int max;
        public MandM(int minn, int maxx) {
            min = minn;
            max = maxx;
        }
    }

    public static void main(String[] args) {
        int n = in.nextInt();
        int[] arr = new int[n];
        arr[0] = in.nextInt();
        MandM mm = new MandM(arr[0], arr[0]);
        for (int i = 1; i < n; i++) {
            arr[i] = in.nextInt();
            if (arr[i] > mm.max) {mm.max = arr[i];}
            if (arr[i] < mm.min) {mm.min = arr[i];}
        }

        out.printf("%d\n%d\n", mm.min, mm.max);
        out.flush();
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

        public int nextInt() {
            return Integer.parseInt(next());
        }
    }
}
