use std::{error::Error, io::{Write, stdout}, thread::sleep, time::Duration};

fn main() -> Result<(), Box<dyn Error>>{
    let txt = "Hello World!".to_string();
    let mut tmp = String::new();

    for val in txt.chars() {
        tmp.push(val);
        print!("\r{}", tmp);
        stdout().flush()?;
        sleep(Duration::from_millis(120));
    }

    println!();
    Ok(())
}