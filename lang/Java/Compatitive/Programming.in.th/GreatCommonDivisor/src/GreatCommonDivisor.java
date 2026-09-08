import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.StringTokenizer;
import java.util.Vector;

public class GreatCommonDivisor {
    private static FastInput in = new FastInput(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));

    public static void main(String[] args) {
        GCDivisor x = new GCDivisor(in.nextLineInt());
        out.println(x.findCommon());
        out.flush();
    }

    static class GCDivisor {
        Vector<Integer> nums;
        int min;
        
        public GCDivisor(Vector<Integer> input) {
            nums = input;
            
            if (nums.size() > 0) {
                min = nums.get(0);
                for (int val: nums) {
                    if (val < min) {
                        min = val;
                    }
                }
            }
        }
        
        public int findCommon() {
            if (nums.size() <= 0) {return 0;}

            boolean inDivisible;
            int common = 1, cadidate = (min % 2 == 0)? 2: 3;

                while (cadidate <= min) {
                    inDivisible = false;
                    for (int val: nums) {
                        if (val % cadidate != 0) {
                            inDivisible = true;
                            break;
                        }
                    }

                    if (!inDivisible) {
                        common = cadidate;
                    }

                    cadidate += (min % 2 == 0)? 1: 2;
                }

            return common;
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
            stt = new StringTokenizer(nextLine());
            
            while (stt.hasMoreTokens()) {
                vec.add(Integer.parseInt(stt.nextToken()));
            }

            return vec;
        }
    }
}
