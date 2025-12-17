use std::io;

fn input() -> String {
    let mut buf = String::new();
    io::stdin().read_line(&mut buf).unwrap();
    buf
}

fn main() {
    let mut sol: Solution = Solution::default();
    while let val = input().trim().to_string() && val != String::from("") {
        sol.nums.push(val.parse::<i32>().unwrap());
    }
    sol.target = input()
        .trim()
        .parse()
        .unwrap();
    
    println!("{}", sol.two_sum().iter().map(|x| x.to_string()).collect::<Vec<String>>().join(" "));
}

#[derive(Debug)]
struct Solution {
    nums: Vec<i32>,
    target: i32
}

impl Default for Solution {
    fn default() -> Self {
        Solution { nums: Vec::new(), target: 0 }
    }
}

impl Solution {
    pub fn two_sum(&mut self) -> Vec<i32> {
        let mut ans: Vec<i32> = Vec::with_capacity(2);
        'outer: for i in 0..self.nums.len() {
            for j in 0..i {
                if self.nums[i] + self.nums[j] == self.target {
                    ans = vec![j as i32, i as i32];
                    break 'outer; 
                }
            }
        }
        ans
    }
}
