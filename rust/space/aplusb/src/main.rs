use std::{
    io::{self, BufRead},
    num::ParseIntError,
};

struct Input {
    tokens: Vec<String>,
}

impl Input {
    fn new(reader: &mut dyn BufRead) -> Self {
        let mut input = String::new();
        reader.read_line(&mut input).expect("Failed to read line");
        let tokens: Vec<String> = input
            .trim()
            .split_whitespace()
            .map(|s| s.to_string())
            .collect();
        Input { tokens }
    }

    fn next_token(&mut self) -> Option<String> {
        self.tokens.pop()
    }

    fn next_int(&mut self) -> Result<i32, ParseIntError> {
        match self.next_token() {
            Some(token) => token.parse::<i32>(),
            None => Err("No token available".parse::<i32>().unwrap_err()),
        }
    }
}

fn main() {
    let stdin = io::stdin();
    let mut input = Input::new(&mut stdin.lock());

    match (input.next_int(), input.next_int()) {
        (Ok(a), Ok(b)) => println!("{}", a + b),
        (Err(_), Ok(_)) | (Ok(_), Err(_)) | (Err(_), Err(_)) => println!("Error parsing input"),
    }
}
