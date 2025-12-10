use std::io;

fn main(){
    let mut rsin = String::new();
    io::stdin().read_line(&mut rsin).unwrap();
    println!("{}", rsin.trim());
    rsin.clear();
}
