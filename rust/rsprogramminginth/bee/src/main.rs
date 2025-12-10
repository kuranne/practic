use std::io;

#[derive(Debug)]
struct Bee {
    amount: i32,
    worker: i32,
    soldier: i32
}

fn input() -> String {
    let mut buf = String::with_capacity(1024);
    io::stdin().read_line(&mut buf).unwrap_or_default();
    buf
}

fn bee_in_year(year: i32, beese: &mut Vec<Bee>) -> Vec<(i32, i32)>{
    let mut wanda: Vec<(i32, i32)> = Vec::new();
    for _ in 1..=year {
        let old_worker: i32 = beese[1].amount;
        let old_soldier: i32 = beese[2].amount;

        beese[1].amount += beese[0].amount * beese[0].worker 
                        + old_worker * beese[1].worker 
                        + old_soldier * beese[2].worker 
                        - old_worker;
        
        beese[2].amount += beese[0].amount * beese[0].soldier 
                        + old_worker * beese[1].soldier 
                        + old_soldier * beese[2].soldier 
                        - old_soldier;

        wanda.push((beese[1].amount, beese[0].amount + beese[1].amount + beese[2].amount));
    }
    wanda
}

fn main() {
    let year: Vec<_> = input()
        .trim()
        .split_whitespace()
        .map(|x| x.parse::<i32>().expect("int32"))
        .collect();

    let mut beese: Vec<Bee> = vec![Bee{amount:1, worker: 1, soldier:0}, Bee{amount:1, worker: 1, soldier:1}, Bee{amount:0, worker: 1, soldier:0}];
    let pre_bee:Vec<_> = bee_in_year(*year.iter().max().unwrap(), &mut beese);
    for mut i in year {
        i -= 1;
        if i > -1 {
            println!("{} {}", pre_bee[i as usize].0, pre_bee[i as usize].1)
        }
    }
}