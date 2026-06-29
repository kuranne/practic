import java.io.IOException;

public class RawInput {
    public static void main(String[] args) throws IOException, InterruptedException {
        String[] cmd = {"/bin/sh", "-c", "stty raw </dev/tty"};
        Runtime.getRuntime().exec(cmd).waitFor();

        try {
            while (true) {
                int input = System.in.read();
                char c = (char)input;

                if (c == 'q') break;

                System.out.println("Recieved: " + c);
            }
        } finally {
            String[] restore_cmd = {"/bin/sh", "-c", "stty cooked </dev/tty"};
            Runtime.getRuntime().exec(restore_cmd).waitFor();
        }
    }
}
