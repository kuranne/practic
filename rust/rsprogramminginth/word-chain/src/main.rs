use std::{io::{self, BufRead}, iter::zip};

fn input(
    stdin: &mut impl BufRead,
    buf: &mut String
) {
    buf.clear();
    stdin.read_line(buf).ok();
}

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let mut stdin = io::stdin().lock();
    let mut buf = String::with_capacity(1024);

    for _ in 0..2 {
        input(&mut stdin, &mut buf);
    }

    let index = buf
        .trim()
        .parse::<usize>()?;

    let mut prev = String::new();
    'outer: for i in 0..index {
        input(&mut stdin, &mut buf);
        
        if i == 0 {
            prev = buf.clone();
            continue;
        }
        
        let mut count = 0;
        for (cur, prev) in zip(buf.chars(), prev.chars()) {
            if cur != prev {
                count += 1;
            }

            if count > 2 {
                break 'outer;
            }
        }

        prev = buf.clone();
    }

    println!("{}", prev);

    Ok(())
}