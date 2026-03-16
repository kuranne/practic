use std::io::{self, BufRead};

fn fibonaci(n: usize) -> i128 {
    if n <= 1 {
        return 1;
    } else {
        return fibonaci(n - 1) + fibonaci(n - 2)
    }
}

fn main() -> Result<(), Box<dyn std::error::Error>>{
    let mut stdin = io::stdin().lock();
    let mut buf = String::with_capacity(32);
    match input(&mut stdin, &mut buf) {
        Ok(()) => (),
        Err(e) => eprintln!("{e}")
    }

    println!("{}", fibonaci(
        buf
        .trim()
        .parse::<usize>()?
    ));
    Ok(())
}

fn input(stdin: &mut impl BufRead, buf: &mut String) -> Result<(), io::Error> {
    buf.clear();
    stdin.read_line(buf)?;
    Ok(())
}