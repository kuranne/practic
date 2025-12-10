use std::{io::{self, BufRead}};

fn input(stdin: &mut impl BufRead, buf: &mut String) {
    buf.clear();
    stdin.read_line(buf).unwrap_or(1);
}

fn prnt(chr: &char, spe: char, sp: &usize) {
    for i in 0..3 {
        print!("{}", if *sp == 3 && i == 1 {*chr} else if (i + *sp) % 2 == 0 {spe} else {'.'})
    }
}

fn main() -> io::Result<()> {
    let mut stdin = io::stdin().lock();
    let mut buf = String::with_capacity(16);
    input(&mut stdin, &mut buf);
    let len: usize = buf.trim().len();

    for line in 1..=5 {
        print!("{}", if line % 3 == 0 {'#'} else {'.'});
        for w in 1..=len {
            prnt(&buf.chars().nth(w - 1).expect("error at nth char l27"),
            if w % 3 == 0 {'*'} else {'#'}, 
            &line);

            if line == 3 {
                print!("{}", if w % 3 == 1 || (w % 3 == 2 && w == len) {'#'} else {'*'})
            } 
            else {
                print!(".")
            }

        }
        println!();
    }

    Ok(())
}
