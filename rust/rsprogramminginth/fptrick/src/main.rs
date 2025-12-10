use std::io;

fn input() -> String {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    input
}

fn mnpow (n: usize) -> String {
    let mut res: String = String::from("1");
    for _ in 0..n {
        let mut xcd = 0;
        let mut temp: String = String::new();

        for i in res.chars().rev() {
            let j = i.to_digit(10).unwrap() * 2 + xcd;
            xcd = j / 10;
            temp.push(char::from_digit(j % 10, 10).unwrap());
        }

        if xcd > 0 {
            temp.push(char::from_digit(xcd, 10).unwrap());
        }
        res = temp.chars().rev().collect();
    }
    return res;
}

fn main() {
    let n: i32 = input().trim().parse().unwrap();
    let mut nums: Vec<String> = vec![];
    for _ in 0..n {
        let tmp: usize = input().trim().parse().unwrap();
        nums.push(mnpow(tmp));
    }

    for i in nums {
        println!("{}", i)
    }
}