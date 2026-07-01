package action;


import java.awt.event.*;

import javax.swing.Timer;

public class TestAction {
    public interface ActionListener {
        public void actionPerformed(ActionEvent envent);
    }

    public class MyListener implements ActionListener {
        protected int time = 0;

        public MyListener() {}

        @Override
        public void actionPerformed(ActionEvent envent) {
            time++;
            if (time > 5) {
                System.out.println("Finish");
            }
        }
    }

    public static void main(String[] args) {
        MyListener listener = new MyListener();
        Timer timer = new Timer(10, listener);
        timer.start();
    }
}