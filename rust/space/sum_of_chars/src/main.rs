use std::io::{self, BufRead};

#[allow(unused)]
enum ReadMode {
    Line,
    All
}
struct Solution;

fn main() -> Result<(), Box<dyn std::error::Error>>{
    let mut stdin = io::stdin().lock();
    let mut buf = String::new();
    match input(ReadMode::Line, &mut stdin, &mut buf) {
        Ok(()) => (),
        Err(e) => eprintln!("{e}")
    }

    println!("{}", Solution::sum_of_char(buf.trim().to_string()) % 12 + 1);

    Ok(())
}

fn input(mode:ReadMode, stdin: &mut impl BufRead, buf: &mut String) -> Result<(), io::Error> {
    buf.clear();
    match mode {
        ReadMode::Line => stdin.read_line(buf)?,
        ReadMode::All => stdin.read_to_string(buf)?
    };
    Ok(())
}

impl Solution {
    fn sum_of_char(txt: String) -> i32 {
        let mut sum: i32 = 0;
        for c in txt.chars() {
            let next = c as u8;
            sum += match next {
                b'A' ..= b'Z' => (next - b'A' + 27) as i32,
                b'a' ..= b'z' => (next - b'a' + 1) as i32,
                _ => 0
            };
        }
        sum
    }
}