#[derive(Debug)]
pub struct Student {
    pub name: String,
    score: i32,
}

pub trait Cheat {
    fn cheat(&mut self, score: i32);
}

pub trait New {
    fn new(name: String) -> Self;
}

#[derive(Debug)]
pub struct Classroom {
    pub amount: i32,
    pub students: Vec<Student>,
}

impl Default for Classroom {
    fn default() -> Self {
        Classroom {
            amount: 0,
            students: Vec::new(),
        }
    }
}

impl New for Student {
    fn new(name: String) -> Self {
        Student { 
            name: name, 
            score: 0
        }
    }
}

impl Cheat for Student {
    fn cheat(&mut self, score: i32) {
        self.score = score;
    }
}

impl Student {
    pub fn get_score(&self) -> i32 {
        self.score
    }
}

impl Classroom {
    pub fn update_amount(&mut self) {
        self.amount = self.students.len() as i32;
    }
    pub fn update_student(&mut self, stu: Student) {
        self.students.push(stu);
        self.update_amount();
    }
}
