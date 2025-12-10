use std::io;

fn input() -> String {
    let mut buf = String::new();
    io::stdin().read_line(&mut buf).unwrap_or_default();
    buf.trim().to_string()
}

fn main() -> io::Result<()> {
    let n: usize = 10;
    let mut ans: Vec<usize> = Vec::new();

    for _ in 0..n {
        let buf = input()
            .parse::<usize>()
            .expect("error at main.rs:14 cause out of degit base?") % 42;
        if !ans.contains(&buf) {ans.push(buf)}
    }

    println!("{}", ans.len());

    Ok(())
}
