use std::io;

fn input() -> String {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    return input;
}

fn main(){
    let x1s: Vec<i32> = input().split_whitespace().map(|x| x.parse().unwrap()).collect();
    println!("{}", x1s[1] * 2 - x1s[0]);
}