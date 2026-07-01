use std::io::{self, BufRead};

fn rl(stdin: &mut impl BufRead, buf: &mut String) {
    buf.clear();
    stdin.read_line(buf).expect("Failed to read line");
}

fn main() -> io::Result<()> {
    let mut stdin = io::stdin().lock();
    let mut buf = String::with_capacity(8192); // allocate buffer 8192 bytes
    rl(&mut stdin, &mut buf); // readline >> buf

    let n = buf
        .trim()
        .parse::<usize>()
        .expect("Failed to parse n");

    rl(&mut stdin, &mut buf);
    let nums: Vec<isize> = buf
        .split_whitespace()
        .map(|x| x.parse().unwrap_or_default())
        .collect();

    let mut ans: Vec<isize> = Vec::new();
    let mut max = 0;

    for i in 0..n {
        let mut sum = 0;
        for j in i..n {
            sum += nums[j];
            if sum > max {
                max = sum;
                ans = nums[i..=j].to_vec();
            }
        }
    }

    if ans.len() != 0 {
        for val in ans {print!("{} ", val)}
        println!("\n{}", max)
    } else {
        println!("Empty sequence")
    }
    
    Ok(())
}