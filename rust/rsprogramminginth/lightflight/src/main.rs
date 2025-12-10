use std::io;

fn input() -> String {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    return input;
}
fn main(){
    let nm: Vec<i32> = input().split_whitespace().map(|x| x.parse().unwrap()).collect();
    let n = nm[0];

    let lk: Vec<i32> = input().split_whitespace().map(|x| x.parse().unwrap()).collect();
    let l = lk[0]; let k = lk[1];

    let c: i32 = input().trim().parse().unwrap();
    let mut expense = 0;

    for _ in 0..n{
        let row: Vec<i32> = input().split_whitespace().map(|x| x.parse().unwrap()).collect();
        for &val in &row{
            expense += val;
        }
    }
    expense += l*k*c;
    expense = if expense % c == 0 {expense/c} else {expense/c + 1};
    println!("{}", expense);
}