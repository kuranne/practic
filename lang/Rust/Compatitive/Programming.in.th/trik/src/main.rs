use std::{
    error::Error,
    io::{self, BufRead},
};

fn input(stdin: &mut impl BufRead, buf: &mut String) -> Result<(), std::io::Error> {
    stdin.read_line(buf)?;
    Ok(())
}

fn main() -> Result<(), Box<dyn Error>> {
    let mut stdin = io::stdin().lock();
    let mut buf = String::with_capacity(51);

    match input(&mut stdin, &mut buf) {
        Ok(()) => (),
        Err(e) => eprintln!("{e}"),
    }

    let mut solver = Solution::from([true, false, false]);
    println!("{}", solver.solve(&buf));

    Ok(())
}

struct Solution {
    cup: Vec<bool>,
}

impl From<[bool; 3]> for Solution {
    fn from(arr: [bool; 3]) -> Self {
        Self {
            cup: Vec::from(arr),
        }
    }
}

impl Solution {
    fn solve(&mut self, input: &String) -> usize {
        let cmd: Vec<char> = input.trim().chars().collect();

        for c in &cmd {
            if *c == 'A' {
                self.cup.swap(0, 1);
            } else if *c == 'B' {
                self.cup.swap(1, 2);
            } else {
                self.cup.swap(0, 2);
            }
        }

        for i in 1..=3 {
            if self.cup[i - 1] {
                return i;
            }
        }

        0
    }
}
