import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.StringTokenizer;
import java.util.Vector;

public class input {
    private static FastInput in = new FastInput(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));

    public static void main(String[] args) {
        double[] arr = in.nextLineDouble();
        for (double item: arr) {
            out.println(item);
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
        public float nextFloat() {
            return Float.parseFloat(next());
        }
        public double nextDouble() {
            return Double.parseDouble(next());
        }

        public String nextLine() {
            try {
                return br.readLine();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
        public int[] nextLineInt() {
            Vector<Integer> vec = new Vector<>();
            stt = new StringTokenizer(nextLine());

            while (stt.hasMoreTokens()) {
                vec.add(Integer.parseInt(stt.nextToken()));
            }

            int[] arr = new int[vec.size()];
            for (int i = 0; i < vec.size(); i++) {
                arr[i] = vec.get(i);
            }

            return arr;
        }
        public float[] nextLineFloat() {
            Vector<Float> vec = new Vector<>();
            stt = new StringTokenizer(nextLine());

            while (stt.hasMoreTokens()) {
                vec.add(Float.parseFloat(stt.nextToken()));
            }

            float[] arr = new float[vec.size()];
            for (int i = 0; i < vec.size(); i++) {
                arr[i] = vec.get(i);
            }

            return arr;
        }
        public double[] nextLineDouble() {
            Vector<Double> vec = new Vector<>();
            stt = new StringTokenizer(nextLine());

            while (stt.hasMoreTokens()) {
                vec.add(Double.parseDouble(stt.nextToken()));
            }

            double[] arr = new double[vec.size()];
            for (int i = 0; i < vec.size(); i++) {
                arr[i] = vec.get(i);
            }

            return arr;
        }
    }

}
