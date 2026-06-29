use std::{ error::Error, io::{ self, Read }, num::ParseIntError, usize, vec::IntoIter };

struct Scanner {
    token: IntoIter<String>,
}

struct Solving {
    board: Vec<String>,
    word: Vec<String>,
    format: Vec<(i32, i32)>,
    coordinate: (usize, usize),
}

fn main() -> Result<(), Box<dyn Error>> {
    let mut input = Scanner::new()?;
    let mut solver = Solving::new(&mut input)?;
    solver.solve();
    Ok(())
}

impl Scanner {
    fn new() -> Result<Self, io::Error> {
        let mut buf = String::new();
        io::stdin().read_to_string(&mut buf)?;
        let token = buf
            .split_whitespace()
            .map(|x| x.to_string())
            .collect::<Vec<String>>()
            .into_iter();

        Ok(Self { token })
    }

    fn next(&mut self) -> Option<String> {
        self.token.next()
    }
}

impl Solving {
    fn new(input: &mut Scanner) -> Result<Self, ParseIntError> {
        let mut board: Vec<String> = Vec::new();
        let mut word: Vec<String> = Vec::new();
        let mut coordinate: Vec<usize> = Vec::new();
        for _ in 0..2 {
            if let Some(val) = input.next() {
                coordinate.push(val.parse::<usize>()?);
            }
        }

        for _ in 0..coordinate[0] {
            if let Some(val) = input.next() {
                board.push(val.to_lowercase());
            }
        }

        if let Some(val) = input.next() {
            for _ in 0..val.parse::<i32>()? {
                if let Some(uiia) = input.next() {
                    word.push(uiia.to_lowercase());
                }
            }
        }

        let format: Vec<(i32, i32)> = vec![
            (-1, 1),
            (0, 1),
            (1, 1),
            (1, 0),
            (1, -1),
            (0, -1),
            (-1, -1),
            (-1, 0)
        ];

        Ok(Self {
            board,
            word,
            format,
            coordinate: (coordinate[0], coordinate[1]),
        })
    }

    fn read(&self, format: &(i32, i32), mut pos: (i32, i32), word: &String) -> usize {
        let mut score = 0;

        'outer: while
            pos.0 >= 0 &&
            pos.1 >= 0 &&
            pos.0 < (self.coordinate.0 as i32) &&
            pos.1 < (self.coordinate.1 as i32)
        {
            if let Some(val) = self.board.get(pos.0 as usize) {
                if let Some(c) = val.chars().nth(pos.1 as usize) {
                    if let Some(x) = word.chars().nth(score) {
                        if x == c {
                            score += 1;
                        } else {
                            break 'outer;
                        }
                    }
                }
            }
            pos.0 += format.0;
            pos.1 += format.1;
        }

        score
    }

    fn solve(&mut self) {
        for w in &self.word {
            let mut highest: (usize, usize, usize) = (0, 0, 0);
            for row in 0..self.coordinate.0 {
                for col in 0..self.coordinate.1 {
                    for f in &self.format {
                        let x = self.read(f, (row as i32, col as i32), w);
                        if x > highest.0 {
                            highest.0 = x;
                            highest.1 = row;
                            highest.2 = col;
                        }
                    }
                }
            }

            println!("{} {}", highest.1, highest.2);
        }
    }
}
