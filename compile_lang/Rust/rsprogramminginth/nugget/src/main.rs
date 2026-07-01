use std::io;

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let number: i32 = input.trim().parse().unwrap();
    input.clear();

    

    if number >= 6 {
        let mut arry: Vec<i32> = vec![0; 3];

        for six in 0..=number / 6 {
            for nine in 0..=number / 9 {
                for twenty in 0..=number / 20 {
                    if six * 6 + nine * 9 + twenty * 20 <= number {
                        arry[0] += six;
                        arry[1] += nine;
                        arry[2] += twenty;
                    }
                }
            }
        }

        let mut numvec: Vec<i32> = Vec::new();
        for i in 0..=arry[0] {
            for j in 0..=arry[1] {
                for k in 0..=arry[2] {
                    let x = 6 * i + 9 * j + 20 * k;
                    if x > number {
                        break;
                    }
                    if !numvec.contains(&x) && x != 0 && x <= number{
                        numvec.push(x);
                    }
                }
            }
        }

        numvec.sort();
        for i in numvec {
            println!("{}", i);
        }
    } else {
        println!("no");
    }
}
