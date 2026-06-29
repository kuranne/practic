use std::{ io::{ self, Read }, vec::IntoIter };

pub struct TokenReader {
    token: IntoIter<String>,
}

impl TokenReader {
    pub fn new() -> Self {
        let mut stdin = io::stdin().lock();
        let mut buf = String::new();

        match stdin.read_to_string(&mut buf) {
            Ok(0) => {
                buf = String::from("");
            }
            Ok(_) => (),
            Err(e) => eprintln!("Error while real to string: {}", e),
        }

        let token: IntoIter<String> = buf
            .split_whitespace()
            .map(|x| x.to_string())
            .collect::<Vec<String>>()
            .into_iter();

        Self {
            token,
        }
    }

    pub fn next(&mut self) -> Option<String> {
        self.token.next()
    }
}
