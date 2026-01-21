public class BoxTest {
    public static void main(String[] args) {
        Box<String> name = new Box<>("Maisa");
        Box<Integer> age = new Box<>(18);
        Box<Double> gpa = new Box<>(3.81);
        System.out.printf("%s %d %f\n", name.getItem(), age.getItem(), gpa.getItem());
    }
}
