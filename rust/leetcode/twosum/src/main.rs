use core::num;
use std::{error::Error, io::{self, BufRead}};

#[allow(unused)]
enum ReadMode {
    Line,
    All
}

fn rsin(mode: ReadMode, stdin: &mut impl BufRead, buf: &mut String) -> Result<(), Box<io::Error>>{
    buf.clear();
    match mode {
        ReadMode::All => stdin.read_to_string(buf)?,
        ReadMode::Line => stdin.read_line(buf)?
    };
    Ok(())
}

fn main() -> Result<(), Box<dyn Error>> {
    let mut stdin = io::stdin().lock();
    let mut buf = String::with_capacity(128);
    
    match rsin(ReadMode::All, &mut stdin, &mut buf) {
        Ok(()) => (),
        Err(e) => eprintln!("{e}")
    }

    let numbers: Vec<i32> = buf
        .split_whitespace()
        .map(|x| x.parse::<i32>())
        .collect::<Result<Vec<i32>, num::ParseIntError>>()?;

    if let Some(target) = numbers.last() {
        println!("{:?}", Solution::two_sum(numbers[0..numbers.len()-1].to_vec(), *target))
    }

    Ok(())
}

#[derive(Debug)]
struct Solution;

impl Solution {
    pub fn two_sum(nums: Vec<i32>, target: i32) -> Vec<i32> {
        for i in 0..nums.len() {
            for j in i + 1..nums.len() {
                if i != j && nums[i] + nums[j] == target {
                    return vec![i as i32, j as i32]
                }
            }
        }
        vec![-1, -1]
    }
}