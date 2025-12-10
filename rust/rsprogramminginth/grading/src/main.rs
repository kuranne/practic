use std::io::{self, BufRead};

fn input(stdin: &mut impl BufRead, buf: &mut String) {
    buf.clear();
    stdin.read_line(buf).unwrap();
}

fn grading(sc: usize) -> &'static str {
    match sc {
        80..=100 => "A",
        75..80 => "B+",
        70..75 => "B",
        65..70 => "C+",
        60..65 => "C",
        55..60 => "D+",
        50..55 => "D",
        _ => "F"
    }
}

fn main() {
    let mut stdin = io::stdin().lock();
    let mut buf = String::with_capacity(3);

    let mut score: usize = 0;
    for _ in 0..3 {
        input(&mut stdin, &mut buf);
        score += buf
            .trim()
            .parse::<usize>()
            .unwrap();
    }

    println!("{}", grading(score).to_string());
}