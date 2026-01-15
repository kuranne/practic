mod school;
use crate::school::classroom::{Cheat, Classroom, New, Student};

fn main() {
    let mut class_a: Classroom = Classroom::default();
    let stu: Student = Student::new("Maisa".to_string());

    class_a.update_student(stu);
    
    for mut student in class_a.students {
        student.cheat(999);
        println!("name {} with score {}.", student.name, student.get_score());
    }
}
