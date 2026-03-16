use std::ops::{Add, Div, Mul, Sub};

struct Calculator;
impl Calculator {
    fn add<T: Add<Output = T>>(a: T, b: T) -> T{
        a + b
    }
    fn minus<T: Sub<Output = T>>(a: T, b: T) -> T{
        a - b
    }
    fn multi<T: Mul<Output = T>>(a: T, b: T) -> T{
        a * b
    }
    fn divide<T: Div<Output = T>>(a: T, b: T) -> T{
        a / b
    }
}

fn main() {
    let a = 10.1;
    let b = 5.2;

    println!(
        "{} {} {} {}",
        Calculator::add(a, b),
        Calculator::minus(a, b),
        Calculator::multi(a, b),
        Calculator::divide(a, b)
    );
}
