use std::io;

fn input() -> String {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    input.trim().to_string()
}

fn chained(a:&str, b:&str) -> bool {
    let mut count: usize;
        count = 0;
    for (i, j) in a.chars().zip(b.chars()) {
        if i != j {count += 1}
        if count > 2 {return false}
    }
    true
}

fn main(){
    let _length: usize = input().parse().unwrap();
    let line: usize = input().parse().unwrap();

    let mut array_str: Vec<String> = vec![];
    let mut temp: String = input();
    array_str.push(temp);

    for i in 1..line {
        temp = input();
        if chained(&array_str[i-1], &temp) {
            array_str.push(temp);
        } else {
            break;
        }
    }

    if array_str.len() > 1 {
        println!("{}", array_str[array_str.len() - 1 ]);
    }else {
        println!("{}", array_str[0]);
    }
}