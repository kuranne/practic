use std::io::{self, BufRead};

#[derive(Debug)]
struct Dice {
    top: usize,
    fnt: usize,
    lft: usize,
    bhd: usize,
    rgt: usize,
    btm: usize
}

impl Default for Dice {
    fn default() -> Self {
        Dice { top: 1, fnt: 2, lft: 3, bhd: 5, rgt: 4, btm: 6 }
    }
}

fn input(stdin: &mut impl BufRead, buf: &mut String) {
    buf.clear();
    stdin.read_line(buf).unwrap_or_default();
}

fn rolling(dice: &Dice, cmd: char) -> Dice{
    let mut tmp: Dice = Dice::default();
    match cmd {
        'F' => {tmp.top = dice.bhd; tmp.fnt = dice.top; tmp.lft = dice.lft; tmp.bhd = dice.btm; tmp.rgt = dice.rgt; tmp.btm = dice.fnt},
        'B' => {tmp.top = dice.fnt; tmp.fnt = dice.btm; tmp.lft = dice.lft; tmp.bhd = dice.top; tmp.rgt = dice.rgt; tmp.btm = dice.bhd},
        'L' => {tmp.top = dice.rgt; tmp.fnt = dice.fnt; tmp.lft = dice.top; tmp.bhd = dice.bhd; tmp.rgt = dice.btm; tmp.btm = dice.lft},
        'R' => {tmp.top = dice.lft; tmp.fnt = dice.fnt; tmp.lft = dice.btm; tmp.bhd = dice.bhd; tmp.rgt = dice.top; tmp.btm = dice.rgt},
        'C' => {tmp.top = dice.top; tmp.fnt = dice.rgt; tmp.lft = dice.fnt; tmp.bhd = dice.lft; tmp.rgt = dice.bhd; tmp.btm = dice.btm},
        'D' => {tmp.top = dice.top; tmp.fnt = dice.lft; tmp.lft = dice.bhd; tmp.bhd = dice.rgt; tmp.rgt = dice.fnt; tmp.btm = dice.btm},
        _ => {tmp.top = dice.top; tmp.fnt = dice.fnt; tmp.lft = dice.lft; tmp.bhd = dice.bhd; tmp.rgt = dice.rgt; tmp.btm = dice.btm}
    }
    tmp
}

fn main() -> io::Result<()>{
    let mut stdin = io::stdin().lock();
    let mut buf = String::with_capacity(1024);
    input(&mut stdin, &mut buf);

    let n: usize = buf
        .trim()
        .parse()
        .expect("usize");

    let mut lst: Vec<Dice> = Vec::new();

    for _ in 0..n {
        input(&mut stdin, &mut buf);
        let cmd: String = buf
            .trim()
            .to_string();
        let mut dice = Dice::default();
        for c in cmd.chars() {
            dice = rolling(&dice, c);
        }
        lst.push(dice);
    }

    for i in lst {
        print!("{} ", i.fnt);
    }
    println!();
    Ok(())
}
