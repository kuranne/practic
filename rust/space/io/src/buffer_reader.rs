use std::io::{ self, BufRead, Read };

pub struct BufferReader;

impl BufferReader {
    pub fn read_line() -> String {
        let mut stdin = io::stdin().lock();
        let mut buf = String::new();

        match stdin.read_line(&mut buf) {
            Ok(_) => (),
            Err(e) => eprintln!("Failed while reading the line: {}", e),
        }

        buf
    }

    pub fn read_to_string() -> String {
        let mut stdin = io::stdin().lock();
        let mut buf = String::new();

        match stdin.read_to_string(&mut buf) {
            Ok(_) => (),
            Err(e) => eprintln!("Failed while reading: {}", e),
        }

        buf
    }
}
