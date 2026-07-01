public class Multitheading {
    public static void main(String[] args) {

        Thread thread1 = new Thread(new MyThreading("Maisa"));
        Thread thread2 = new Thread(new MyThreading("Kuranne"));

        thread1.start();
        thread2.start();

        try {
            thread1.join();
            thread2.join();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }
}
