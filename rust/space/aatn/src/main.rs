use std::{io};

#[derive(Debug)]
struct Num {
    num: i32,
    sequence: u32
}

fn input() -> String {
    let mut buf = String::new();
    io::stdin().read_line(&mut buf).unwrap_or_default();
    buf
}


fn main() -> io::Result<()>{
    let mut arry: Vec<Num> = Vec::new();
    println!("Input for an, am and aq");
    for _ in 0..2 {
        let temp: Vec<i32> = input()
            .split_whitespace()
            .map(|x| x.parse().expect("Int!"))
            .collect();
        arry.push(Num {num: temp[0], sequence: temp[1].try_into().unwrap_or_default()});
    }

    let n = input()
        .trim()
        .parse::<u32>()
        .expect("int!");

    let d: i32 = (arry[1].num - arry[0].num) / ((arry[1].sequence - arry[0].sequence) ) as i32;
    println!(
        "{}",
        arry[0].num + d * ((n - arry[0].sequence) as i32)
    );

    Ok(())
}