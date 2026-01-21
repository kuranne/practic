use std::io;

fn input() -> String {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    return input;
}

fn main() {
    let n: usize = input().trim().parse().unwrap();
    let mut nums: Vec<String> = vec![];
    
    for _ in 0..n {
        let temp = input().trim().to_string();
        nums.push(temp);
    }

    let mut res: char;

    for i in nums {
        if i.len() == 1{
            if i.chars().nth(0).unwrap().to_digit(10).unwrap() == 2 {
                res = 'T';
            }else if i.chars().nth(0).unwrap().to_digit(10).unwrap() % 2 != 0{
                res = 'T';
            }else {
                res = 'F';
            }
        }else {
            let rev_i = i.chars().nth_back(0).unwrap();
            let int_t = rev_i.to_digit(10).unwrap();
            res = if int_t % 2 == 1 {'T'} else {'F'};
        }
        println!("{}", res);

    }

}