use std::io;

fn input() -> String{
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    return input;
}

fn main() {
    let n: i32= input()
        .trim()
        .parse()
        .unwrap();
    
    let mut mooks: Vec<String> = Vec::new();
    let mut checkin: bool;
    
    for _ in 0..n {
        let temp:String = input().trim().to_string();
        checkin = true;
        for i in &mooks {
            if temp == *i {
                checkin = false;
                break;
            }
        }
        if checkin {
            mooks.push(temp);
        }
    }
    
    mooks.sort();
    for i in mooks {
        println!("{}", i);
    }

}
