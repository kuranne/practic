use serde::Deserialize;
use std::{error::Error, io::{Write, stdout}, process::Command, thread::sleep, time::Duration};

#[allow(unused)]
#[derive(Debug, Deserialize)]
struct MyIP {
    ip: String,
    country: String,
    cc: String
}

impl Default for MyIP {
    fn default() -> Self {
        MyIP { ip: "".to_string(), country: "".to_string(), cc: "".to_string() }
    }
}

#[tokio::main]
async fn fetch(myip: &mut MyIP, url: &String) -> Result<(), reqwest::Error> {
    *myip = reqwest::get(url)
        .await?
        .json()
        .await?;

    Ok(())
}

fn main() -> Result<(), Box<dyn Error>> {
    let mut myip: MyIP = MyIP::default();
    let url: String = "https://api.myip.com".to_string();

    print!("requesting to {}", url);
    stdout().flush()?;
    for _ in 0..3 {
        print!(".");
        stdout().flush()?;
        sleep(Duration::from_millis(750));
    }

    let mut child = Command::new("sleep").arg("2").spawn()?;
    child.wait()?;

    match fetch(&mut myip, &url) {
        Ok(()) => println!("\rYour ip is {}, in {}.", myip.ip, myip.country),
        Err(e) => eprintln!("\rFailed to get api due to {e}")
    }

    Ok(())
}