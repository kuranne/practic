use std::{io::{self, Write}, thread::sleep, time::Duration};

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let text: String = "Hello World!".to_string();
    let mut output_stream: String = "".to_string();

    for c in text.chars() {
        output_stream.push(c);
        print!("\r{}", output_stream);
        io::stdout().flush()?;
        sleep(Duration::from_millis(180));
    }

    println!();

    Ok(())
}