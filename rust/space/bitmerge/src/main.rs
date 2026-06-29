use std::error::Error;

use io::token_reader::TokenReader;
use bitmerge::BitMerge;

fn main() -> Result<(), Box<dyn Error>> {
    let mut input = TokenReader::new();

    while let Some(bit_line) = input.next() {
        println!("{}", BitMerge::merge_form::<String>(bit_line));
    }

    Ok(())
}
