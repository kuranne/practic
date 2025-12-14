use std::{io::{self, BufRead}, num::ParseIntError};

fn rsin(stdin: &mut impl BufRead, buf: &mut String) -> Result<(), io::Error> {
    buf.clear();
    stdin.read_to_string(buf)?;
    Ok(())
}

fn parse_usize(data: &String) -> Result<Vec<usize>, ParseIntError> {
    let vector: Vec<usize> = data
        .split_whitespace()
        .map(|x| x.parse::<usize>())
        .collect::<Result<Vec<usize>, ParseIntError>>()?;
    Ok(vector)
}

fn main() -> Result<(), Box<dyn::std::error::Error>> {
    let mut stdin = io::stdin().lock();
    let mut input = String::with_capacity(128);
    
    match rsin(&mut stdin, &mut input) {
        Ok(()) => {input = input.trim().to_string();},
        Err(e) => {eprintln!("Failed to read stdin: {e}")} 
    }

    let mut dwraves: Vec<usize> = Vec::new();
    match parse_usize(&input) {
        Ok(res) => {dwraves = res;},
        Err(e) => eprintln!("Failed to: {e}")
    }

    let target: usize = dwraves.iter().sum::<usize>() - 100usize;

    'lvl1 : for x1 in dwraves.clone() {
        for x2 in dwraves.clone() {
            if x1 + x2 == target {
               dwraves.retain(|&x| x != x1 && x != x2);
               break 'lvl1;
            }
        }
    }

    println!("{}", dwraves.iter().map(|x| x.to_string()).collect::<Vec<String>>().join("\n"));

    Ok(())
}