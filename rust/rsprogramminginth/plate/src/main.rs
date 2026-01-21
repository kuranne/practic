use std::{collections::HashMap, io::{self, BufRead}};

fn input(stdin: &mut impl BufRead, buff: &mut String) {
    buff.clear();
    stdin.read_line(buff).unwrap();
}

fn check_cmd(s: &String, chk: &str) -> bool {
    s.split_whitespace().any(|x| x == chk)
}

fn main() {
    let mut stdin = io::stdin().lock();
    let mut buff = String::new();
    
    input(&mut stdin, &mut buff);
    let yp: Vec<usize> = buff
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();

    let mut students: HashMap<usize, usize> = HashMap::new();
    
    for _ in 0..yp[1] {
        input(&mut stdin, &mut buff);
        let temp: Vec<usize> = buff
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect();
        students.insert(temp[1], temp[0]);
    }

    let mut line: Vec<(usize, usize)> = Vec::new();
    let mut ans: Vec<usize> = Vec::new();

    loop {
        input(&mut stdin, &mut buff);
        if check_cmd(&buff, "X") {
            break;
        } else if check_cmd(&buff, "D") {
            if !line.is_empty() {
                ans.push(line.remove(0).1);
            } else {
                println!("empty")
            }
        } else {
            let temp: Vec<&str> = buff
                .split_whitespace()
                .collect();

            let stu_id = temp[1].parse::<usize>().unwrap();
            if let Some((_, &year)) = students.get_key_value(&stu_id) {
                let student: (usize, usize) = (year, stu_id);

                if line.len() > 1 {
                    for i in 0..line.len() {
                        if i < line.len() - 1 {
                            if line[i].0 != line[i + 1].0 && line[i].0 == year {
                                line.insert(i + 1, student);
                                break;
                            } 
                        } else if i == line.len() - 1 {
                            line.push(student);
                        }
                    }
                } else {
                    line.push(student);
                }
            }
        }
    }

    ans.push(0);
    for val in ans {
        println!("{}", val)
    }
}