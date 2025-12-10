use std::io::{self, BufRead};

fn input(stdin: &mut impl BufRead, buf: &mut String) {
    buf.clear();
    stdin.read_line(buf).unwrap_or_default();
}

fn main() -> io::Result<()> {
    // Intilize stdin & buffer
    let mut stdin = io::stdin().lock();
    let mut buf = String::with_capacity(64);
    input(&mut stdin, &mut buf);

    // Vec for N & M
    let nm: Vec<usize> = buf
        .trim()
        .split_whitespace()
        .map(|x| x.parse().expect("not int"))
        .collect();
    
    // Node with weight
    let mut node: Vec<Vec<usize>> = Vec::new();
    for _ in 0..nm[0] {
        input(&mut stdin, &mut buf);
        node.push(buf.trim().split_whitespace().map(|x| x.parse().expect("not int")).collect());
    }

    

    Ok(())
}
