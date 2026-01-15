package func.io;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class FastInput {
    BufferedReader br;
    StringTokenizer stt;

    public FastInput(InputStream in) {
        this.br = new BufferedReader(new InputStreamReader(in));
        this.stt = new StringTokenizer("");
    }

    public String next() {
        while (!this.stt.hasMoreTokens()) {
            try {
                this.stt = new StringTokenizer(this.br.readLine());
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
        return stt.nextToken();
    }

    public String nextLine() {
        try {
            return br.readLine();
        } catch (IOException e) {
            throw new RuntimeException(e);
        } 
    }

    public int nextInt() {
        return Integer.parseInt(this.next());
    }

    public int[] nextLineInt() {
        ArrayList<Integer> arrl = new ArrayList<>();
        this.stt = new StringTokenizer(this.nextLine());
        
        while (this.stt.hasMoreTokens()) {
            arrl.add(Integer.valueOf(this.stt.nextToken()));
        }

        int[] arr = new int[arrl.size()];

        for (int i = 0; i < arrl.size(); i++) {
            arr[i] = arrl.get(i);
        }

        return arr;
    }
}
