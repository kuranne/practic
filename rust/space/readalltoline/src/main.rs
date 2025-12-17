use std::{error::Error, io::{self, BufRead}};

#[allow(unused)]
enum ReadMode {
    Line,
    All
}

fn rsin(mode: ReadMode, stdin: &mut impl BufRead, buf: &mut String) -> Result<(), io::Error> {
    buf.clear();
    match mode {
        ReadMode::All => stdin.read_to_string(buf)?,
        ReadMode::Line => stdin.read_line(buf)?
    };
    Ok(())
}

fn trim_line(txt: String) -> Vec<String> {
    let vec: Vec<String> = txt
        .lines()
        .map(String::from)
        .collect();
    vec
}

fn main() -> Result<(), Box<dyn Error>> {
    let mut stdin = io::stdin().lock();
    let mut buf = String::new();
    
    match rsin(ReadMode::All, &mut stdin, &mut buf) {
        Ok(()) => (),
        Err(e) => eprintln!("Error: {e}")
    }

    let data: Vec<String> = trim_line(buf);
    println!("{}", data.join(" "));

    Ok(())
}