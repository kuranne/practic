public class EmailPraser {
    public static void main(String[] args) {
        String email = "kuramais@gmail.com";
        String name = email.substring(0, email.indexOf("@"));
        String domain = email.substring(email.indexOf("@") + 1, email.length());
        System.out.printf("name: %s\ndomain name: %s\n", name, domain);
    }
}
