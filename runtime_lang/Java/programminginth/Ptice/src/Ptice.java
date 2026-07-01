import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;
import java.util.StringTokenizer;
import java.util.Vector;

public class Ptice {
    public record SandI(Vector<String> name, int score) {}

    private static FastInput in = new FastInput(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));

    public static void main(String[] args) {
        Question q = new Question(in.nextInt(), in.next());
        SandI tmp = q.highestScore();
        out.println(tmp.score);
        for (String s: tmp.name) {
            out.println(s);
        }
        out.flush();
    }

    static class Pattern {
        char[] Adrian = {'A', 'B', 'C'};
        char[] Bruno = {'B', 'A', 'B', 'C'};
        char[] Goran = {'C', 'C', 'A', 'A', 'B', 'B'};

        public HashMap<String, Integer> sumScore(int size, char[] ques) {
            HashMap<String, Integer> map = new HashMap<>();
            map.put("Adrian", 0);
            map.put("Bruno", 0);
            map.put("Goran", 0);
            
            for (int i = 0; i < size; i++) {
                if (ques[i] == Adrian[i%3]) {map.replace("Adrian", map.get("Adrian") + 1);}
                if (ques[i] == Bruno[i%4]) {map.replace("Bruno", map.get("Bruno") + 1);}
                if (ques[i] == Goran[i%6]) {map.replace("Goran", map.get("Goran") + 1);}
            }

            return map;
        }
    }

    static class Question extends Pattern {
        int n;
        String txt;
        
        public Question(int inputn, String inputtxt) {
            n = inputn;
            txt = inputtxt;
        }
        
        public SandI highestScore() {
            int max = 0;
            Vector<String> name = new Vector<>();
            HashMap<String, Integer> tmp = super.sumScore(n, txt.toCharArray());

            max = Math.max(tmp.get("Adrian"), Math.max(tmp.get("Bruno"), tmp.get("Goran")));

            for (Map.Entry<String, Integer> val: tmp.entrySet()) {
                if (val.getValue() == max) {name.add(val.getKey());}
            }

            Collections.sort(name);

            return new SandI(name, max);
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

        public int nextInt() {
            return Integer.parseInt(next());
        }
    }
}
