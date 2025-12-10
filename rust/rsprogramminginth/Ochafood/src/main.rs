use std::io;

fn input() -> String {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    return input;
}

fn premutate (gone:Vec<i32>, remain:Vec<i32>, result: &mut Vec<Vec<i32>>) {
    if remain.is_empty() {result.push(gone);}
    else {
        for i in 0..remain.len() {
            let mut gone_temp = gone.clone();
            gone_temp.push(remain[i]);
            let mut remain_temp = remain.clone();
            remain_temp.remove(i);

            premutate(gone_temp, remain_temp, result);
        }
    }

} 

fn main() {
    let num: Vec<i32> = (1..=input().trim().parse().unwrap()).collect();
    let _m = input();
    let exclude:Vec<i32> = input()
        .trim()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();
    let mut result: Vec<Vec<i32>> = Vec::new();

    premutate(vec![], num, &mut result);
    result.retain(|x| !exclude.contains(&x[0]));
    result.sort();

    for i in result {
        let l: String = i
            .iter()
            .map(|x| x.to_string())
            .collect::<Vec<String>>()
            .join(" ");
        println!("{}", l);
    }

}