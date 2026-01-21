
import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class PrimeOdd {
    private static final PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
    private static final FastInput in = new FastInput(System.in);

    public static void main(String[] args) {
        ArrayList<Integer> numbers = new ArrayList<>();
        int n = in.nextInt();
        
        for (int i = 0; i < n; i++) {
            numbers.add(in.nextInt());
        }

        Solution sol = new Solution(numbers);
        for (boolean p: sol.answer) {
            out.println((p) ? "T" : "F");
        }
        out.flush();
    }

    private static class Solution {
        private final ArrayList<Integer> primes;
        public ArrayList<Boolean> answer;

        public Solution(ArrayList<Integer> numbers) {
            this.primes = new ArrayList<>();
            this.answer = new ArrayList<>();

            int limit = numbers.get(0);

            for (int num: numbers) {
                if (isOdd(num)) {
                    this.answer.add(true);
                    if (limit < num) {limit = num;}
                } else if (num == 2){
                    this.answer.add(true);
                }
                  else {
                    this.answer.add(false);
                }
            }

            this.primes.add(2);
            if (limit > 2 && isOdd(limit)) {
                for (int i = 3; i <= limit; i+=2) {
                    if (isPrime(i)) {
                        this.primes.add(i);
                    }
                }
            }

            for (int i = 0; i < this.answer.size(); i++) {
                if (this.answer.get(i) && !this.primes.contains(numbers.get(i)) && numbers.get(i) > 2) {
                    this.answer.set(i, false);
                }
            }
        }

        private boolean isPrime(int number) {
            for (int prime: this.primes) {
                if (number % prime == 0) {
                    return false;
                }
            }
            return true;
        }

        private boolean isOdd(int number) {
            return number % 2 != 0;
        }
    }

    private static class FastInput {
        private final BufferedReader br;
        private StringTokenizer stt;

        public FastInput(InputStream in) {
            this.br = new BufferedReader(new InputStreamReader(in));
            this.stt = new StringTokenizer("");
        }

        public String next() {
            while (!this.stt.hasMoreTokens()) {
                try { 
                    this.stt = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
            return this.stt.nextToken();
        }

        public int nextInt() {
            return Integer.parseInt(this.next());
        }
    }
}
