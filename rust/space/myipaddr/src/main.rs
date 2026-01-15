use serde::Deserialize;
use std::{error::Error};

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
async fn request_api(myip: &mut MyIP, url: &String) -> Result<(), reqwest::Error> {
    *myip = reqwest::get(url)
        .await?
        .json()
        .await?;

    Ok(())
}

fn main() -> Result<(), Box<dyn Error>> {
    let mut myip: MyIP = MyIP::default();
    let ip_url: String = "https://api.myip.com".to_string();
    let libre_speedtest_url: String = "https://librespeed.org/backend".to_string();

    match request_api(&mut myip, &ip_url) {
        Ok(()) => (),
        Err(e) => eprintln!("\rFailed to get api due to {e}")
    }



    Ok(())
}