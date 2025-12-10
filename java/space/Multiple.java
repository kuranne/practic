import java.util.Scanner;

public class Multiple {
    public static void main(String[] args) {
        Scanner jvIn = new Scanner(System.in);

        System.out.println("Enter the INT number");
        int varA = jvIn.nextInt();
        jvIn.close();

        for(int i = 1; i <= 12; i++){
            System.out.printf("%d * %d = %d" +'\n', varA, i, varA * i);
        }
        System.out.println("------------");
    }
}
