use std::{io, iter::zip};

fn input() -> String {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    input.trim().to_string()
}

fn check_gap(col: &Vec<i128>, mapping: &Vec<i128>) -> i32 {
    let mut result: i32 = 0;
    let mut t: usize = 0;
    if col[0] > 1 {
        while (mapping.len() as isize - t as isize - (col[0] as isize)) >= 0 {
            let base = mapping[t] + col[1];
            for (c, i) in zip(col[2..].iter(), 1..col.len()) {
                if *c + mapping[t + i] != base {
                    break;
                }
                if col[0] as usize == i + 1 {
                    result += 1;
                }
            }
            t += 1;
        }
    } else {
        result += mapping.len() as i32;
    }
    result
}

fn main() {
    // read
    let _tcol: usize = input().parse().unwrap();
    let mapcol: Vec<i128> = input()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();
    let qnums: usize = input().parse().unwrap();
    let mut bcol: Vec<Vec<i128>> = Vec::new();

    for _ in 0..qnums {
        bcol.push(
            input()
                .split_whitespace()
                .map(|x| x.parse().unwrap())
                .collect(),
        );
    }
    // end of read
    for col in &bcol {
        println!("{}", check_gap(col, &mapcol));
    }
}
