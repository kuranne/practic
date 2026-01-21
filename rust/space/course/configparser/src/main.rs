use configparser::ini::Ini;

fn main(){
    let mut config = Ini::new();
    config.load("./src/config.ini").unwrap();
    let value = config.get("subject", "a").unwrap();
    println!("{}", value);
}