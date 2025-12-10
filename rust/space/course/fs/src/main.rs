use std::{fs, io};

fn input() -> String {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    input.trim().to_string()
}
fn main() {
    let mut content = fs::read_to_string("./fs/src/config.ini").unwrap();
    println!("{}", content);
    println!("sel a, b: ");
    if input() == "a" {
        content += "\n[core]\nwait = true\n";
        let _result = fs::write("./fs/src/config.ini", content).unwrap();
        content = fs::read_to_string("./fs/src/config.ini").unwrap();
    }else {
        let _result = fs::write("./fs/src/config.ini", "");
        content = fs::read_to_string("./fs/src/config.ini").unwrap();
    }

    println!("{}", content);
}