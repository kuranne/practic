use std::io::{self, BufRead};

#[derive(Debug, Default)]
struct Base32 {
    decimal: i32,
    binary: Vec<usize>,
    bin_limit: u32,
    bin_length: usize
}

impl Base32 {
    pub fn set_decimal_to(&mut self, number: i32) {
        self.decimal = number;
    }

    pub fn parse_binary(&mut self) -> String {
        const TWO: i32 = 2;

        self.bin_limit = self.decimal.ilog(2);
        let mut tmp = self.decimal;

        for i in (0..=self.bin_limit).rev() {
            let next = TWO.pow(i);
            if tmp >= next {
                tmp -= next;
                self.binary.push(1)
            } else {
                self.binary.push(0)
            }
        }

        self.bin_length = self.binary.len();
        if self.bin_length % 5 != 0 {
            self.binary.reverse();
            while self.bin_length % 5 != 0 {
                self.binary.push(0);
                self.bin_length += 1
            }
            self.binary.reverse();
        }

        // dbg!(&self.binary);

        self.binary.iter().map(|x| x.to_string()).collect::<String>()
    }

    pub fn parse_base_32(&mut self) -> String {
        const TWO: usize = 2;

        if self.bin_length <= 0 {
           let _pb = self.parse_binary();
        }

        let mut number  = "".to_string();
        let mut i = 0;

        while number.len() < self.bin_length / 5 {
            let section: Vec<usize> = self.binary[(i * 5)..((i + 1) * 5)].to_vec();
            let mut tmp = 0;
            for j in 0..5 {
                tmp += section[j] * TWO.pow(4 - (j as u32))
            }
            number.push(
                match tmp {
                    0..=9 => ((tmp as u8) + b'0') as char,
                    _ => ((tmp as u8) - 10u8 + b'A') as char
                }
            );
            i += 1
        }

        number
    }
}

fn input(stdin: &mut impl BufRead, buf: &mut String) -> Result<(), io::Error>{
    buf.clear();
    stdin.read_line(buf)?;
    Ok(())
}

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let mut stdin = io::stdin().lock();
    let mut buf = String::with_capacity(16);
    match input(&mut stdin, &mut buf) {
        Ok(()) => (),
        Err(e) => eprintln!("{e}")
    }

    let mut solve: Base32 = Base32::default();
    solve.set_decimal_to(
        buf
            .trim()
            .parse::<i32>()?
    );

    println!(
        "{}",
        solve.parse_base_32()
    );
    Ok(())
}
