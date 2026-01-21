import java.util.Scanner;

public class SayMyName {
    public static void main(String[] args) {
        try (Scanner scanner = new Scanner(System.in)) {
            String name = scanner.next();
            System.out.printf("Hello %s!\n", name);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }
}
