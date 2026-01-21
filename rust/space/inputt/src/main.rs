use std::{error::Error, io::{self, BufRead, Write}, num::{ParseFloatError}};

struct FastInput<R: BufRead> {
    reader: R,
    buf: String
}

impl <R: BufRead> FastInput<R> {
    fn new(reader: R) -> Self {
        Self { reader, buf: String::new() }
    }

    #[allow(unused)]
    fn next<T: std::str::FromStr>(&mut self) -> Result<T, Box<dyn Error>> {
        loop {
            if let Some(token) = self.buf.split_whitespace().next() {
                let res = token.parse().map_err(|_| "Parse Error")?;
                self.buf = self.buf.split_off(token.len());
                return Ok(res);
            }
            self.buf.clear();
            self.reader.read_line(&mut self.buf)?;
        }
    }

    fn next_line_double(&mut self) -> Result<Vec<f64>, Box<dyn Error>> {
        self.buf.clear();
        self.reader.read_line(&mut self.buf)?;
        Ok(self.buf
            .split_whitespace()
            .map(|x| x.parse::<f64>())
            .collect::<Result<Vec<f64>, ParseFloatError>>()?)
    }
}

fn main() -> Result<(), Box<dyn Error>>{
    let mut input = FastInput::new(io::stdin().lock());
    let mut out = io::BufWriter::new(io::stdout().lock());

    let data = input.next_line_double()?;
    for item in data {
        match writeln!(out, "{}", item) {
            Ok(()) => (),
            Err(e) => eprint!("Error: {e}")
        }
    }
    out.flush()?;

    Ok(())
}
