use std::{collections::HashMap, io::{self, BufRead}, num::ParseIntError, usize};

enum ReadMode {
    Line,
    All
}

fn rsin(mode: ReadMode, stdin: &mut impl BufRead, buf: &mut String) -> Result<(), io::Error> {
    buf.clear();

    match mode {
        ReadMode::Line => stdin.read_line(buf)?,
        ReadMode::All => stdin.read_to_string(buf)?
    };

    Ok(())
}

fn mapping(mapp: &mut HashMap<String, usize>) {
    mapp.insert(" _ | ||_|".to_string(), 0);
    mapp.insert("     |  |".to_string(), 1);
    mapp.insert(" _  _||_ ".to_string(), 2);
    mapp.insert(" _  _| _|".to_string(), 3);
    mapp.insert("   |_|  |".to_string(), 4);
    mapp.insert(" _ |_  _|".to_string(), 5);
    mapp.insert(" _ |_ |_|".to_string(), 6);
    mapp.insert(" _   |  |".to_string(), 7);
    mapp.insert(" _ |_||_|".to_string(), 8);
    mapp.insert(" _ |_| _|".to_string(), 9);
}

fn main() -> Result<(), Box<dyn std::error::Error>>{
    let mut stdin = io::stdin().lock();
    let mut buf = String::new();
    match rsin(ReadMode::Line, &mut stdin, &mut buf) {
        Ok(()) => (),
        Err(e) => eprintln!("Error: {e}")
    }

    let aandb: Vec<usize> = buf
        .trim()
        .split_whitespace()
        .map(|x| x.parse::<usize>())
        .collect::<Result<Vec<usize>, ParseIntError>>()?;

    match rsin(ReadMode::All, &mut stdin, &mut buf) {
        Ok(()) => (),
        Err(e) => eprintln!("Error: {e}")
    }

    let abvec: Vec<Vec<char>> = buf
        .lines()
        .map(|l| l.chars().collect::<Vec<char>>())
        .collect();

    let mut x: SevenSegment = SevenSegment { ab: aandb, vec: abvec };
    println!("{}", x.plusss()?);

    Ok(())
}

struct SevenSegment {
    ab: Vec<usize>,
    vec: Vec<Vec<char>>
}

impl SevenSegment {
    fn parse_pic(&mut self, n: usize, mapp: &HashMap::<String, usize>) -> Result<usize, Box<dyn std::error::Error>>{
        
        let mut word: usize = 0;
        let mut arr: Vec<usize> = Vec::new();

        while arr.len() != self.ab[n] {
            let mut tmp: String = String::new();
            
            for i in if n == 0 {0..3} else {3..6} {
                for j in word..word + 3 {
                    tmp.push(self.vec[i][j]);
                }
            }

            if let Some(val) = mapp.get(&tmp) {arr.push(*val);}
            word += 4;
        }
        
        let mut i: usize = f64::powf(10.0, self.ab[n] as f64) as usize;
        let mut number: usize = 0;
        for val in arr {
            i /= 10;
            number += i * val;
        }

        Ok(number)
    }

    fn plusss(&mut self) -> Result<usize, Box<dyn std::error::Error>> {
        let mut mapp: HashMap<String, usize> = HashMap::new();
        mapping(&mut mapp);
        Ok(self.parse_pic(0, &mapp)? + self.parse_pic(1, &mapp)?)
    }
}