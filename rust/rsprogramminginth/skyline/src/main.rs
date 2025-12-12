use std::{io::{self, BufRead}, iter::zip};

#[derive(Debug)]
struct Building {
    x: usize,
    h: usize,
    y: usize,
}

impl Default for Building {
    fn default() -> Self {
        Building { x: 0, h: 0, y: 0 }
    }
}

impl From<Vec<usize>> for Building {
    fn from(vec: Vec<usize>) -> Self {
        if vec.len() != 3 {
            panic!("expect 3 value of usize")
        }
        Building {
            x: vec[0],
            h: vec[1],
            y: vec[2],
        }
    }
}

fn input(stdin: &mut impl BufRead, buf: &mut String) {
    buf.clear();
    stdin.read_line(buf).unwrap_or_default();
}

fn main() -> io::Result<()> {
    let olint: String = "Only int is allowed!".to_string();

    let mut stdin = io::stdin().lock();
    let mut buf = String::with_capacity(32);
    input(&mut stdin, &mut buf);

    let n = buf.trim().parse::<usize>().expect(&olint);

    let mut map: Vec<usize> = Vec::new();

    for _ in 0..n {
        input(&mut stdin, &mut buf);
        let xhy: Building = Building::from(
            buf.trim()
                .split_whitespace()
                .map(|x| x.parse::<usize>().expect(&olint))
                .collect::<Vec<usize>>()
        );
        
        if map.len() < xhy.y {map.resize(xhy.y, 0usize);}
        
        for i in xhy.x-1..xhy.y-1 {
            if map[i] < xhy.h {map[i] = xhy.h.clone()}
        }
    }

    map.resize(map.len() + 1, 0);

    let mut prev: usize = 0usize;
    for (i, val) in zip(1..map.len(), map.clone()) {
        if val != prev {
            print!("{} {} ", i, val);
        }
        prev = val;
    }
    println!();

    Ok(())
}
