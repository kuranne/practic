use std::io::{self, BufRead};

fn input(stdio: &mut impl BufRead, buf: &mut String) {
    buf.clear();
    stdio.read_line(buf).unwrap();
}

fn swipe(x: &String) -> String {
    let mut y: String = String::with_capacity(x.len());
    let mut xl: usize = x.len();
    while xl != 0 {
        y.push(x.chars().nth(xl - 1).unwrap());
        xl -= 1;
    }
    y
}

fn main() -> io::Result<()> {
    let mut stdio = io::stdin().lock();
    let mut buf = String::new();
    input(&mut stdio, &mut buf);
    let x = buf.trim().to_string();
    let y = swipe(&x);
    if x == y {
        println!("ispalindome")
    } else {
        println!("isn'tpalindome")
    }
    Ok(())
}