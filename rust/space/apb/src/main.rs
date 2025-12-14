use std::io::{self, BufRead, BufReader};

fn main() -> io::Result<()>{
    let mut reader = BufReader::new(io::stdin());
    let mut buf: Vec<u8> = Vec::new();

    let bytes_read = reader.read_until(b' ', &mut buf).unwrap();

    let mut txt: String = String::new();
    
    if bytes_read > 0 {
        match String::from_utf8(buf) {
            Ok(s) => txt = s,
            Err(e) => panic!("Failed to utf8 cause {}", e),
        }
    }

    print!("{txt}");
    Ok(())
}