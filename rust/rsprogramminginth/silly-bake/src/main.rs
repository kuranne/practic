use std::{ error::Error, io::{ self, BufRead }, num::ParseIntError, vec::IntoIter };

fn main() -> Result<(), Box<dyn Error>> {
    let mut input: Input = Input::new();
    let mut shop: Shop = Shop::new(&mut input)?;
    match shop.solve(&mut input) {
        Ok(()) => (),
        Err(e) => eprintln!("{}", e),
    }

    Ok(())
}

#[derive(Debug)]
struct Input {
    token: IntoIter<IntoIter<String>>,
}

impl Input {
    fn new() -> Self {
        let mut stdin = io::stdin().lock();
        let mut buf = String::new();
        let mut total: Vec<IntoIter<String>> = Vec::new();

        loop {
            buf.clear();
            let mut line: Vec<String> = Vec::new();
            match stdin.read_line(&mut buf) {
                Ok(0) => {
                    break;
                }
                Ok(_) => {
                    line = buf
                        .split_whitespace()
                        .map(|x| x.to_string())
                        .collect();
                }
                Err(e) => eprintln!("{}", e),
            }
            total.push(line.into_iter());
        }

        Self {
            token: total.into_iter(),
        }
    }
}

struct Shop;

impl Shop {
    fn new(input: &mut Input) -> Result<Self, Box<dyn Error>> {
        let _customer = input.token.next().ok_or("ntl")?;
        Ok(Self {})
    }

    fn solve(&mut self, input: &mut Input) -> Result<(), Box<dyn Error>> {
        let preset: [i32; 5] = [8, 6, 4, 2, 1];
        let mut total_orders: [i32; 5] = [0; 5];

        while let Some(customer) = input.token.next() {
            let order: Vec<i32> = customer
                .map(|x| x.parse::<i32>())
                .collect::<Result<Vec<i32>, ParseIntError>>()?;
            for i in 0..5 {
                total_orders[i] += order[i];
            }
        }

        let mut used_cake = 0;
        let mut fragments: Vec<i32> = Vec::new();
        for i in 0..5 {
            let piece_size = preset[i];
            let mut amount = total_orders[i];

            for left in fragments.iter_mut() {
                if amount <= 0 {
                    break;
                }
                let can_fit = *left / piece_size;
                let take = can_fit.min(amount);
                *left -= take * piece_size;
                amount -= take;
            }

            while amount > 0 {
                used_cake += 1;
                let mut new_cake_space = 8;
                let take = (new_cake_space / piece_size).min(amount);
                new_cake_space -= take * piece_size;
                amount -= take;

                if new_cake_space > 0 {
                    fragments.push(new_cake_space);
                }
            }
            fragments.retain(|&x| x > 0);
        }

        println!("{}", used_cake);
        Ok(())
    }
}
