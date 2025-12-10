use std::io;

fn input() -> String {
    let mut input: String= String::new();
    io::stdin().read_line(&mut input).unwrap();
    input
}

fn main(){
    let n: usize = input().trim().parse().unwrap();
    let mut ans: Vec<u64> = vec![];
    for x in 0..n {
        let ques:u64 = input().trim().parse().unwrap();
        ans.push(0);
            for i in 1..=ques {
                for j in 1..=ques+i {
                    for k in 1..=ques+i+j {
                        ans[x] += (i*j*k) % (i+j+k);
                    }
                }
        }
    }
    for i in ans {
        println!("{}", i);
    }
}