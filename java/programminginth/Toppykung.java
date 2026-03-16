
import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.StringTokenizer;

public class Toppykung {
    private static final FastInput in = new FastInput(System.in);
    private static final PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));

    public static void main(String[] args) {
        int n = in.nextInt();
        for (int i = 0; i < n; i++) {
            new Solution(in.next());
        }
        for (String txt: Solution.getSortList()) {
            out.println(txt);
        }
        out.flush();
    }

    private static class Solution {
        private static ArrayList<String> list = new ArrayList<>();

        public Solution(String word) {
            if (!list.contains(word)) {
                list.add(word);
            }
        }

        public static ArrayList<String> getSortList() {
            sortList();
            return list;
        }

        private static void sortList() {
            Collections.sort(list);
        }
    }

    private static class FastInput {
        private final BufferedReader br;
        private StringTokenizer stt;

        public FastInput(InputStream in) {
            br = new BufferedReader(new InputStreamReader(in));
            stt = new StringTokenizer("");
        }

        public String next() {
            while (!stt.hasMoreTokens()) {
                try {
                    stt = new StringTokenizer(br.readLine());
                } catch(IOException e) {
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