use std::{ error::Error, io::{ self, Read }, num::ParseIntError, vec::IntoIter };

struct Input {
    token: IntoIter<String>,
}

impl Input {
    fn new() -> Result<Self, Box<dyn Error>> {
        let mut buf = String::new();
        io::stdin().read_to_string(&mut buf)?;
        let token = buf
            .split_whitespace()
            .map(|x| x.to_string())
            .collect::<Vec<String>>();
        Ok(Self { token: token.into_iter() })
    }
}

fn main() -> Result<(), Box<dyn Error>> {
    let mut input = Input::new()?;
    let mut low: Vec<i64> = Vec::new();

    Ok(())
}
