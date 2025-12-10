use std::io;

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();

    let n: i32 = input
        .trim()
        .parse()
        .unwrap();
    
    input.clear();

    let res: f64;
    let sqt: f64 = f64::sqrt(3.0);
    
    if n <= 2 {res = 2.0}else
    if n % 2 == 0 {res = n as f64}else 
    if n == 3 {res = 2.0 + sqt} 
    else {res = 2.0 * (sqt + 1.0) + f64::from(n) - 5.0}

    println!("{:.6}", res);
}
