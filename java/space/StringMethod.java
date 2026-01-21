public class StringMethod {
    public static void main(String[] args) {
        String name = "Kuranne";
        char[] nameArr = name.toCharArray();
        System.out.printf("at 2: %c with %d\n", nameArr[2], name.length());    
    }
}
