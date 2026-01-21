public class MyThreading implements Runnable {
    private String text;
    public MyThreading(String text) {
        this.text = text;
    }

    @Override
    public void run() {
        for (int i = 0; i < 5; i ++) {
            try {
                Thread.sleep(1000);
                System.out.println(text);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }
    }
}
