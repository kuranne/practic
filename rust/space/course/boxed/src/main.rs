/*
#[derive(Debug)]
enum List<T> {
    Cons(T, Box<List<T>>),
    Nil,
}
*/

fn main() {
    let x: u8 = 1;
    let boxed: Box<u8> = Box::from(x);

    for i in 0..*boxed {
        println!("{}", i)
    }

    let boxslide: Box<[i32]> = (0..4).collect();
    for item in boxslide.into_iter().enumerate() {
        let (i, val): (usize, &i32) = item;
        println!("{i}: {val}");
    }

    for item in boxslide.iter().enumerate() {
        let (i, val): (usize, &i32) = item;
        println!("{i}: {val}");
    }
    
    for item in IntoIterator::into_iter(boxslide).enumerate() {
        let (i, val): (usize, i32) = item;
        println!("{i}: {val}");
    }


    /*
    let list: List<u8> = List::Cons(1, Box::new(List::Cons(2, Box::new(List::Nil))));
    println!("{:?}", list);
    */
}