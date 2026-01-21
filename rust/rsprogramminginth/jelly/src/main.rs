use std::{io::{self, BufRead}, num::ParseIntError};

fn input(stdin: &mut impl BufRead, buf: &mut String) -> Result<(), io::Error> {
    buf.clear();
    stdin.read_line(buf)?;
    Ok(())
}

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let mut stdin = io::stdin().lock();
    let mut buf = String::new();
    match input(&mut stdin, &mut buf) {
        Ok(()) => (),
        Err(e) => eprintln!("Failed to read_line: {e}")
    }

    let mut abc: Vec<u32> = buf
        .trim()
        .split_whitespace()
        .map(|x| x.parse::<u32>())
        .collect::<Result<Vec<u32>, ParseIntError>>()?;

    let mut count: u8 = 0;
    while abc.iter().sum::<u32>() > 3u32{
        abc.sort_by(|a, b| b.cmp(a));
        abc[0] /= 2;
        count += 1;
    }

    println!("{}", count);
    Ok(())
}