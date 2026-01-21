import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.StringTokenizer;
import java.util.Vector;

public class SevenDwraves {
    private static FastInput in = new FastInput(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
    
    public static void main(String[] args) {
        Vector<Integer> dwraf = new Vector<>();
        int limit = 100, n = 9, target = 0;
        
       for (int i = 0; i < n; i++) {
            int tmp = in.nextInt();
            dwraf.add(tmp);
            target += tmp;
        }
        target -= limit;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (dwraf.get(i) + dwraf.get(j) == target) {
                    dwraf.remove(i);
                    dwraf.remove(j);
                    i = n; break;
                }
            }
        }

        for (int i: dwraf) {
            out.println(i);
        }
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
