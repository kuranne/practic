import java.io.BufferedOutputStream;
import java.io.PrintWriter;
import java.util.Scanner;

public class grading {
    private static Scanner in = new Scanner(System.in);
    private static PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));

    public static void main(String[] args) {
        int sum = 0;
        for (int i = 0; i < 3; i++) {
            sum += in.nextInt();
        }   
        if (sum >= 80) {out.println("A");} 
        else if (sum >= 75) {out.println("B+");} 
        else if (sum >= 70) {out.println("B");} 
        else if (sum >= 65) {out.println("C+");} 
        else if (sum >= 60) {out.println("C");} 
        else if (sum >= 55) {out.println("D+");} 
        else if (sum >= 50) {out.println("D");}
        else {out.println("F");}
        
        out.flush();
    }
}
