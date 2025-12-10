import java.util.Scanner;

public class AplusB {
    public static void main(String[] args) {
        Scanner jvin = new Scanner(System.in);

        int variable_a = jvin.nextInt(), variable_b = jvin.nextInt();
        jvin.close();

        System.out.printf("Ans is : %d" + "\n", variable_a + variable_b);
    }
}