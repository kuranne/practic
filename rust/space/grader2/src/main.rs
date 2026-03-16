use std::io;

trait New {
    fn new() -> Self;
}

struct Grader;
struct Student {
    score: i32,
    mid: i32,
    fnl: i32
}

fn input(stdin: &mut impl io::BufRead, buf: &mut String) -> Result<(), io::Error> {
    buf.clear();
    stdin.read_line(buf)?;
    Ok(())
}

fn main() -> Result<(), Box<dyn std::error::Error>>{
    let mut stdin = io::stdin().lock();
    let mut buf = String::new();
    let mut person: Student = Student::new();

    match input(&mut stdin, &mut buf) {
        Ok(()) => (),
        Err(e) => eprintln!("{e}")
    }

    let val: Vec<i32> = buf
        .split_whitespace()
        .map(|x| x.parse::<i32>())
        .collect::<Result<Vec<i32>, std::num::ParseIntError>>()?;

    person.set_score(val);

    println!("{}", Grader::grade(person));

    Ok(())
}

impl New for Student {
    fn new() -> Self {
        Student {
            score: 0,
            mid: 0,
            fnl: 0,
        }
    }
}

impl Student {
    pub fn sum(self) -> i32 {
        self.score + self.mid + self.fnl
    }

    pub fn set_score(&mut self, val: Vec<i32>) {
        self.score = val[0];
        self.mid = val[1];
        self.fnl = val[2];
    }
}

impl Grader {
    pub fn grade(stu: Student) -> String {
        let mut ret = "".to_string();
        match stu.sum() {
            80..=100 => ret += "A",
            75..80 => ret += "B+",
            70..75 => ret += "B",
            65..70 => ret += "C+",
            60..65 => ret += "C",
            55..60 => ret += "D+",
            50..55 => ret += "D",
            _ => ret += "F"
        }
        ret
    }
}