use std::io::{self, Read};

fn chained(a: &[u8], b: &[u8]) -> bool {
    let mut count = 0;
    let len = a.len().min(b.len());
    for i in 0..len {
        if a[i] != b[i] {
            count += 1;
            if count > 2 {
                return false;
            }
        }
    }
    true
}

fn main() {
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();

    let mut iter = input.lines();
    let _length: usize = iter.next().unwrap().parse().unwrap();
    let line: usize = iter.next().unwrap().parse().unwrap();

    let mut array_str: Vec<&str> = Vec::with_capacity(line);
    let temp = iter.next().unwrap();
    array_str.push(temp);

    for _ in 1..line {
        if let Some(next) = iter.next() {
            if chained(array_str.last().unwrap().as_bytes(), next.as_bytes()) {
                array_str.push(next);
            } else {
                break;
            }
        }
    }

    println!("{}", array_str.last().unwrap());
}