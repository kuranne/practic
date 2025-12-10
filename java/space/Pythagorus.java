import java.util.Scanner;

public class Pythagorus {
    public static void main(String[] args) {
        Scanner jvin = new Scanner(System.in);

        double var_a = jvin.nextInt();
        double var_b = jvin.nextInt();

        jvin.close();

        double var_c = Math.sqrt(var_a * var_a + var_b * var_b); //c^2 = a^2 + b^2

        System.out.printf("C is %,.6f" + "\n", var_c);
    }    
}
