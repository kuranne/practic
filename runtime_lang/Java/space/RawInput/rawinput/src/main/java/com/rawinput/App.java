package com.rawinput;

import java.io.BufferedOutputStream;
import java.io.IOException;
import java.io.PrintWriter;
import org.jline.terminal.Terminal;
import org.jline.terminal.TerminalBuilder;
import org.jline.utils.NonBlockingReader;

public class App {

    public static void main(String[] args)
        throws IOException, InterruptedException {
        Terminal terminal = TerminalBuilder.terminal();
        terminal.enterRawMode();
        NonBlockingReader reader = terminal.reader();
        int input = reader.read();

        new PrintWriter(new BufferedOutputStream(System.out), true).println(
            input - '0'
        );
    }
}
