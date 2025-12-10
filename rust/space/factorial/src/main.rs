use std::io::{self, BufRead};

fn input(stdin: &mut impl BufRead, buf: &mut String) {
    buf.clear();
    stdin.read_line(buf).expect("Failed to read");
}

fn factorial(n: u128) -> u128{
    if n > 0 {
        return factorial(n - 1) * n;
    }
    return 1
}

fn main() -> io::Result<()>{
    let mut buf = String::new();
    let mut stdin = io::stdin().lock();
    input(&mut stdin, &mut buf);

    println!("{}", factorial(buf
        .trim()
        .parse()
        .expect("number")
    ));

    Ok(())
}