use std::io;

fn rsin() -> i32 {
    let mut rsin = String::new();
    io::stdin().read_line(&mut rsin).unwrap();
    return rsin.trim().parse().unwrap();
}

fn main(){
    let n = rsin(); let mut i = 0;
    let mut number = vec![]; let mut maxn:i32; let mut minn:i32;

    while i < n {
        number.push(rsin());
        i+=1;
    }

    minn = number[0].clone();
    maxn = minn.clone();

    for i in number{
        if maxn < i {maxn = i;}
        if minn > i {minn = i;}
    }

    println!("{}\n{}", minn, maxn);
}