use clap::Parser;

#[derive(Debug, Parser)]
#[command(name = "hello", version, about = "hello world")]
struct Args {
    #[arg(short, long)]
    name: String,
    
    #[arg(short, long, default_value_t = 1)]
    time: u8
}

fn main() {
    let arg = Args::parse();
    if arg.time < 1 {println!("time can't lower than 1."); return;}
    for _ in 0..arg.time {
        println!("Hello {}!", arg.name)
    }
}