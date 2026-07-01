use std::{
    error::Error,
    io::{ self, BufRead },
    num::ParseIntError,
    ops::{ Index, IndexMut },
    vec::IntoIter,
};

fn main() -> Result<(), Box<dyn Error>> {
    let mut input = Input::new()?;
    let mut board = Board::new(&mut input)?;
    let mut solver = Solution::new(&mut input)?;
    match solver.solve(&mut board) {
        Ok(()) => (),
        Err(e) => eprintln!("Unexpect error: {}", e),
    }
    Ok(())
}

macro_rules! mat {
    ($board:expr, $vec2d:expr) => {
        $board[$vec2d.row as usize][$vec2d.col as usize]
    };
}

struct Input {
    token: IntoIter<String>,
}

#[derive(Clone, Copy)]
enum Obj {
    NONE,
    BOARD,
    BLOCK(char),
}

#[derive(Clone, Copy, Debug)]
struct Vec2D {
    row: i32,
    col: i32,
}

#[derive(Clone)]
struct Board {
    scope: Vec2D,
    board: Vec<Vec<Obj>>,
}

struct Solution {
    question: Vec<(Vec2D, char)>,
}

impl Input {
    fn new() -> Result<Self, io::Error> {
        let mut buf = String::new();
        let mut stdin = io::stdin().lock();
        let mut line = Vec::<String>::new();

        loop {
            buf.clear();
            match stdin.read_line(&mut buf) {
                Ok(0) => {
                    break;
                }
                Ok(_) => {
                    line.push(buf.trim().to_string());
                }
                Err(e) => eprintln!("{e}"),
            }
        }

        Ok(Input {
            token: line.into_iter(),
        })
    }
}

impl Index<Vec2D> for Board {
    type Output = Obj;
    fn index(&self, index: Vec2D) -> &Self::Output {
        &self.board[index.row as usize][index.col as usize]
    }
}

impl IndexMut<Vec2D> for Board {
    fn index_mut(&mut self, index: Vec2D) -> &mut Self::Output {
        &mut self.board[index.row as usize][index.col as usize]
    }
}

impl PartialEq for Vec2D {
    fn eq(&self, other: &Self) -> bool {
        self.row == other.row && self.col == other.col
    }
}

impl Vec2D {
    fn add_by(&self, row: i32, col: i32) -> Self {
        Self {
            row: self.row + row,
            col: self.col + col,
        }
    }
}

impl Obj {
    fn new(c: char) -> Self {
        match c {
            '#' => Self::BOARD,
            '-' => Self::NONE,
            _ => Self::BLOCK(c),
        }
    }

    fn get_char(self) -> char {
        match self {
            Self::NONE => '-',
            Self::BOARD => '#',
            Self::BLOCK(b) => b,
        }
    }

    fn is_this(self, c: char) -> bool {
        self.get_char() == c
    }

    fn is_block(self) -> bool {
        match self {
            Self::BLOCK(_) => true,
            _ => false,
        }
    }
}

impl Board {
    fn new(input: &mut Input) -> Result<Self, Box<dyn Error>> {
        let scope: Vec<i32> = input.token
            .next()
            .ok_or("No token left")?
            .split_whitespace()
            .map(|x| x.parse::<i32>())
            .collect::<Result<Vec<i32>, ParseIntError>>()?;

        let mut board = Vec::<Vec<Obj>>::new();

        for _ in 0..scope[0] {
            let mut line = Vec::<Obj>::new();
            if let Some(line_token) = input.token.next() {
                let mut token = line_token.split_whitespace();
                while let Some(t) = token.next() {
                    line.push(Obj::new(t.chars().next().ok_or("ntl")?));
                }
            }
            board.push(line);
        }

        Ok(Self {
            scope: Vec2D { row: scope[0], col: scope[1] },
            board,
        })
    }

    fn is_under(&self, coor: &Vec2D, c: char) -> bool {
        let next_coor = coor.add_by(1, 0);
        if next_coor.row >= self.scope.row {
            return false;
        }

        self[next_coor].is_this(c)
    }

    fn moveto(&mut self, old_coor: Vec2D, new_coor: Vec2D) {
        let (left, right) = (self[old_coor], self[new_coor]);
        mat!(self.board, old_coor) = right;
        mat!(self.board, new_coor) = left;
    }

    fn update(&mut self) -> i32 {
        let mut total_score = 0;
        let mut changed = true;
        let format = [
            [0, 1],
            [1, 0],
            [0, -1],
            [-1, 0],
        ];

        while changed {
            changed = false;

            for row in (0..self.scope.row).rev() {
                for col in (0..self.scope.col).rev() {
                    let mut coor = Vec2D { row, col };
                    if self[coor].is_block() {
                        let mut fell = false;
                        while self.is_under(&coor, '-') {
                            coor.row += 1;
                            fell = true;
                            changed = true;
                        }
                        if fell {
                            self.moveto(Vec2D { row, col }, coor);
                        }
                    }
                }
            }

            for row in 0..self.scope.row {
                for col in 0..self.scope.col {
                    let coor = Vec2D { row, col };
                    if self[coor].is_block() {
                        let score_gained = self.combine(coor, &format);
                        if score_gained > 0 {
                            total_score += score_gained;
                            changed = true;
                        }
                    }
                }
            }
        }
        total_score
    }

    fn combine(&mut self, coor: Vec2D, format: &[[i32; 2]; 4]) -> i32 {
        let mut score = 0;
        let mut to_rm = Vec::<Vec2D>::new();
        to_rm.push(coor);
        self.chain(&coor, &mut to_rm, format);

        if to_rm.len() > 1 {
            for x in to_rm {
                mat!(self.board, x) = Obj::NONE;
                score += 5;
            }
        }
        score
    }

    fn chain(&self, coor: &Vec2D, exclude: &mut Vec<Vec2D>, format: &[[i32; 2]; 4]) {
        for f in format {
            let cadidate_vec2d = coor.add_by(f[0], f[1]);
            if !self.in_scope(cadidate_vec2d) {
                continue;
            }
            if
                self[*coor].is_this(self[cadidate_vec2d].get_char()) &&
                !exclude.contains(&cadidate_vec2d)
            {
                exclude.push(cadidate_vec2d);
                self.chain(&cadidate_vec2d, exclude, format);
            }
        }
    }

    fn in_scope(&self, coordinate: Vec2D) -> bool {
        coordinate.row >= 0 &&
            coordinate.col >= 0 &&
            coordinate.row < self.scope.row &&
            coordinate.col < self.scope.col
    }
}

impl Solution {
    fn new(input: &mut Input) -> Result<Self, Box<dyn Error>> {
        let mut question = Vec::<(Vec2D, char)>::new();
        let _qn = input.token.next().ok_or("ntl")?.trim().parse::<i32>()?;

        while let Some(line) = input.token.next() {
            let mut token = line.split_whitespace();
            let (x, y) = (
                token.next().ok_or("ntl")?.parse::<i32>()?,
                token.next().ok_or("ntl")?.parse::<i32>()?,
            );
            let c = token.next().ok_or("ntl")?.chars().next().ok_or("ntl")?;
            question.push((Vec2D { row: x, col: y }, c));
        }

        Ok(Self {
            question,
        })
    }

    fn solve(&mut self, board: &mut Board) -> Result<(), Box<dyn Error>> {
        let mut score = board.update();
        for ques in &self.question {
            let q_coor = ques.0;
            match board[q_coor] {
                Obj::BOARD | Obj::NONE => {
                    score -= 5;
                    continue;
                }
                _ => (),
            }
            let mut new_q_coor = Vec2D {
                col: q_coor.col +
                (match ques.1 {
                    'L' => -1,
                    'R' => 1,
                    _ => 0,
                }),
                row: q_coor.row,
            };

            match board[new_q_coor] {
                Obj::NONE => {
                    while board.is_under(&new_q_coor, '-') {
                        new_q_coor.row += 1;
                    }
                    board.moveto(q_coor, new_q_coor);
                    score += board.update();
                }
                _ => {
                    score -= 5;
                }
            }
        }

        self.output(score, &board.board);

        Ok(())
    }

    fn output(&self, score: i32, board: &Vec<Vec<Obj>>) {
        println!("{}", score);
        for row in board {
            for col in row {
                print!("{} ", col.get_char());
            }
            println!();
        }
    }
}
