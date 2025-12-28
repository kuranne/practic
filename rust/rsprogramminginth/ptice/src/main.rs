use std::{collections::HashMap, error::Error, io::{self, BufRead}, iter::{zip}};

fn rsin(stdin: &mut impl BufRead, buf: &mut String) -> Result<(), io::Error> {
    buf.clear();
    stdin.read_to_string(buf)?;

    Ok(())
}

struct Pattern {
    adrian: [char; 3],
    bruno: [char; 4],
    goran: [char; 6]
}

impl Default for Pattern {
    fn default() -> Self {
        Pattern { 
            adrian: ['A', 'B', 'C'], 
            bruno: ['B', 'A', 'B', 'C'], 
            goran: ['C', 'C', 'A', 'A', 'B', 'B'] 
        }
    }
}

struct Question {
    n: usize,
    txt: String
}

impl Question {
    fn sum_score(&self) -> HashMap<String, usize>{
        let ptn: Pattern = Pattern::default();
        let mut score: [usize; 3] = [0usize; 3];
        
        for (c, i) in zip(self.txt.chars(), 0..self.n) {
            if c == ptn.adrian[i % 3] {score[0] += 1}
            if c == ptn.bruno[i % 4] {score[1] += 1}
            if c == ptn.goran[i % 6] {score[2] += 1}
        }

        let mut map: HashMap<String, usize> = HashMap::new();
        
        map.insert("Adrian".to_string(), score[0]);
        map.insert("Bruno".to_string(), score[1]);
        map.insert("Goran".to_string(), score[2]);

        map
    }

    fn highest_score(&self) -> (Vec<String>, usize) {
        let map: HashMap<String, usize> = self.sum_score();
        let max: usize = *map.values().max().unwrap_or(&0usize);
        let mut winner: Vec<String> = Vec::new();
        
        for (name, val) in map {
            if max == val {winner.push(name);}
        }

        winner.sort();

        (winner, max)
    }
}

fn main() -> Result<(), Box<dyn Error>> {
    let mut stdin = io::stdin().lock();
    let mut buf = String::with_capacity(128);

    match rsin(&mut stdin, &mut buf) {
        Ok(()) => (),
        Err(e) => eprintln!("{e}")
    }

    let token: Vec<&str> = buf
        .trim()
        .split_whitespace()
        .collect();

    let ques: Question = Question { n: token[0].parse()?, txt: token[1].to_string()};
    let ans = ques.highest_score();
    println!("{}", ans.1);
    for val in ans.0 {
        println!("{}", val)
    }

    Ok(())
}