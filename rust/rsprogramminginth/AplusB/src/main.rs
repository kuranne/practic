use std::io;

fn rsin() -> i32 {
    let mut rsin = String::new();
    io::stdin().read_line(&mut rsin).unwrap();
    return rsin.trim().parse().unwrap();
}

fn main(){
    let a = rsin();
    let b = rsin();
    println!("{}", a+b);
}