import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.io.BufferedOutputStream;
import java.util.StringTokenizer;
import java.util.Vector;

public class Quicksort {
    private static FastInput in = new FastInput(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));    

    public static void main(String[] args) {
        int[] arr = in.nextLineInt();
        sort(arr, 0, arr.length - 1);

        for (int val: arr) {
            out.printf("%d ", val);
        }
        out.println();
        out.flush();
    }

    private static void swap(int[] arr, int a, int b) {
        int tmp = arr[a];
        arr[a] = arr[b];
        arr[b] = tmp;
    }

    private static int partition(int[] arr, int low, int high) {
        int pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr, i, j);
            }
        }
        swap(arr, i + 1, high);

        return i + 1;
    }

    public static void sort(int[] arr, int low, int high) {
        if (low < high) {
            int pivot = partition(arr, low, high);
            sort(arr, low, pivot - 1);
            sort(arr, pivot + 1, high);
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

        public int[] nextLineInt() {
            Vector<Integer> vec = new Vector<>();
            StringTokenizer stt = new StringTokenizer(nextLine());
            
            while (stt.hasMoreTokens()) {
                vec.add(Integer.parseInt(stt.nextToken()));
            }
            int[] arr = new int[vec.size()];

            for (int i = 0; i < vec.size(); i++) {
                arr[i] = vec.get(i);
            }

            return arr;
        }
    }
}
