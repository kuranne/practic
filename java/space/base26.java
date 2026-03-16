import func.io.FastInput;
import java.io.BufferedOutputStream;
import java.io.PrintWriter;

public class base26 {
    private static final PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
    private static final FastInput in = new FastInput(System.in);

    public static void main(String[] args) {
        int number = in.nextInt();
        out.println(Base26_Converter.toBase26(number));
        out.flush();
    }

    public static class Base26_Converter {
        public static int toDigit(String numberString) {
            int num = 0, i = numberString.length();
            int posPow = 1;

            while ((i--) != 0) {
                num += (numberString.charAt(i) - 'A' * posPow);
                posPow *= 26;
            } 

            return num;
        }

        // public static String toBase26(int num) {
        //     String numberString = "";
        //     int limit = (int)Math.sqrt((double)num) - 1;
        //     int x;

        //     for (int i = limit; i >= 0; i--) {
        //         numberString += (char)((((x = (int)Math.pow((double)limit, (double)i)) == 1) ? num : num % x ) + 'A');
        //         num /= 26;
        //     }

        //     return numberString;
        // }
    }

}