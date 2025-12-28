use std::{error::Error, fs::File, io::{Read}, num::ParseIntError};

// fn rsin(stdin: &mut impl BufRead, buf: &mut String) -> Result<(), io::Error> {
//     buf.clear();
//     stdin.read_to_string(buf)?;

//     Ok(())
// }

fn partition(arr: &mut [i32]) -> usize {
    let mut i = 0;

    let pvi = arr.len() - 1;
    let pivot = arr[pvi];

    for j in 0..pvi {
        if arr[j] < pivot {
            arr.swap(i, j);
            i += 1;
        }
    }

    arr.swap(i, pvi);

    i
}

fn quicksort(arr: &mut [i32]) {
    let len = arr.len();
    if len <= 1 {return}

    let pvi = partition(arr);

    quicksort(&mut arr[0..pvi]); // left
    quicksort(&mut arr[pvi + 1..len]); //right
}

fn main() -> Result<(), Box<dyn Error>> {
    // let mut stdin = io::stdin().lock();
    let mut buf = String::new();
    
    // match rsin(&mut stdin, &mut buf) {
    //     Ok(()) => (),
    //     Err(e) => eprintln!("Error: {e}")
    // }

    // let mut vector: Vec<i32> = buf
    //     .trim()
    //     .split_whitespace()
    //     .map(|x| x.parse::<i32>())
    //     .collect::<Result<Vec<i32>, ParseIntError>>()?;

    let mut f = File::open("data.txt")?;
    buf.clear();
    f.read_to_string(&mut buf)?;

    let mut vector: Vec<i32> = buf
        .trim()
        .split_whitespace()
        .map(|x| x.parse::<i32>())
        .collect::<Result<Vec<i32>, ParseIntError>>()?;

    if vector.len() > 1 {
        quicksort(&mut vector);
    }

    for item in vector {
        print!("{} ", item)
    }
    println!();

    Ok(())
}