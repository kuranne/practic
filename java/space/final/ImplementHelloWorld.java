import signature.HelloWorld;

public class ImplementHelloWorld implements HelloWorld {
    public void print(String txt) {
        System.out.println(txt);
    }
    public void print() {
        print(NORMAL_HELLO_WORLD);
    }
}
