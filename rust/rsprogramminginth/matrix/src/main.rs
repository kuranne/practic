use std::{io::{self, BufRead}, iter::zip};

fn input(stdin: &mut impl BufRead, bffr: &mut String) {
    bffr.clear();
    stdin.read_to_string(bffr).unwrap();
}

fn main() -> io::Result<()> {
    let mut stdin = io::stdin().lock();
    let mut bffr = String::with_capacity(1024);
    input(&mut stdin, &mut bffr);

    let number: Vec<i32> = bffr
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();

    let rc: [usize; 2] = [number[0].try_into().unwrap(), number[1].try_into().unwrap()];
    let dt: Vec<i32> = number[2..].to_vec();
    let sz = rc[0] * rc[1];

    for (i, j) in zip(0..sz, sz..sz * 2) {
        print!("{} ", dt[i] + dt[j]);
        if (i + 1) % rc[1] == 0 {
            println!()
        }
    }
    
    Ok(())
}