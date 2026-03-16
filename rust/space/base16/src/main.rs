use std::io;

#[derive(Debug)]
struct Base16;
impl Base16 {
    pub fn parse_binary(number: i32) -> String {
        const TWO: u32 = 2u32;
        let mut binary = "".to_string();
        let limit = number.ilog(2);
        let mut tmp = number;

        for i in (0..=limit).rev() {
            let next = TWO.pow(i) as i32;
            if tmp >= next {
                tmp -= next;
                binary.push(b'1' as char);
            } else {
                binary.push(b'0' as char);
            }
        }
        if binary.len() % 4 != 0 {
            let mut binary_tmp = binary.chars().collect::<Vec::<char>>();
            binary_tmp.reverse();
            while binary_tmp.len() %4 != 0 {
                binary_tmp.push('0');
           }
           binary_tmp.reverse();
           binary = binary_tmp
            .iter()
            .collect::<String>();
        }

        binary
    }

    pub fn parse_hexadecimal(number: i32) -> String {
        const TWO: i32 = 2;
        let binary = Base16::parse_binary(number);
        let limit = binary.len() / 4usize;
        let mut base16_number = String::new();
        
        while base16_number.len() < limit {
            let mut section = binary[( base16_number.len() * 4 )..( (base16_number.len() + 1) * 4)].chars().collect::<Vec<char>>();
            section.reverse();
            let mut tmp = 0;
            
            for i in 0..4 {
                tmp += (if section[i] == '0' {0} else {1}) * (TWO.pow(i as u32) as u8);
            }

            base16_number.push(
                match tmp {
                    0..=9 => (tmp + b'0') as char,
                    10..=15 => (tmp - 10 + b'A') as char,
                    _ => ' '
                }
            );
        }
        base16_number
    }
}


fn main() -> Result<(), Box<dyn std::error::Error>> {
    let mut stdin = io::stdin().lock();
    let mut buf = String::with_capacity(16);
    match input(&mut stdin, &mut buf) {
        Ok(()) => (),
        Err(e) => eprintln!("{e}")
    }

    println!("{}", 
        Base16::parse_hexadecimal(
            buf
            .trim()
            .parse::<i32>()?
        )
    );

    Ok(())
}

fn input(stdin: &mut impl io::BufRead, buf: &mut String) -> Result<(), io::Error> {
    buf.clear();
    stdin.read_line(buf)?;
    Ok(())
}