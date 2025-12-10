use std::io::{self, BufRead};

fn input(stdin: &mut impl BufRead, buf: &mut String) {
    buf.clear();
    stdin.read_line(buf).unwrap_or_default();
}

fn hexagon(n: i32) -> i32{
    if n > 1 {
        return hexagon(n - 1) + (n * 6) - 6;
    }
    1
}

fn main() -> io::Result<()>{
    let mut stdin = io::stdin().lock();
    let mut buf = String::new();
    input(&mut stdin, &mut buf);

    println!("{}", hexagon(buf.trim().parse().expect("number")));

    Ok(())
}
