use std::{io, iter::zip};

fn input() -> String {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap_or_default();
    input.trim().to_string()
}

fn main() -> io::Result<()>{
    let number: i32 = input().parse().unwrap();
    let mappchar: [&str; 9] = ["C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"];
    let mapp:[i32; 9] = [100, 90, 50, 40, 10, 9, 5, 4, 1];
    let mut mappvalue: [i32; 5] = [0; 5];
    for mut nums in 1..=number {
        let mut temp = String::new();
        for (val, i) in zip(mapp, 0..mapp.len()) {
            while nums >= val {
                nums -= val;
                temp += mappchar[i];
            }
        }
        for c in temp.chars() {
            match c {
                'C' => mappvalue[4] += 1,
                'L' => mappvalue[3] += 1,
                'X' => mappvalue[2] += 1,
                'V' => mappvalue[1] += 1,
                'I' => mappvalue[0] += 1,
                _ => {}
            }
        }
    }

    for val in mappvalue {
        print!("{} ", val);
    }

    Ok(())
}