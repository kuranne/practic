use std::{ error::Error, io::{ self, BufRead }, num::ParseIntError, vec::IntoIter };

macro_rules! mat {
    ($mapping:expr, $a:expr) => {
        $mapping[$a.0 as usize][$a.1 as usize]
    };
}

struct Input {
    token: IntoIter<String>,
}

impl Input {
    fn new() -> Result<Self, Box<dyn Error>> {
        let mut buf = String::new();
        let mut stdin = io::stdin().lock();
        let mut lines = Vec::<String>::new();

        loop {
            buf.clear();
            match stdin.read_line(&mut buf) {
                Ok(0) => {
                    break;
                }
                Ok(_) => {
                    lines.push(buf.clone());
                }
                Err(e) => {
                    eprintln!("{}", e);
                    break;
                }
            }
        }

        Ok(Self {
            token: lines.into_iter(),
        })
    }

    fn next_line(&mut self) -> String {
        if let Some(val) = self.token.next() { val } else { "".to_string() }
    }
}

fn main() -> Result<(), Box<dyn Error>> {
    let mut input = Input::new()?;
    let mut board = Board::new(&mut input)?;
    let mut ope = Operator::new(&mut input)?;
    ope.solve(&mut board);
    Ok(())
}

enum Obj {
    NONE,
    BOARD,
    BLOCK(char),
}

struct Board {
    scope: Vec<i32>,
    mapping: Vec<Vec<Obj>>,
}
struct Operator {
    questions: Vec<(i32, i32, char)>,
    score: i32,
}

impl Obj {
    fn new(input: char) -> Self {
        match input {
            '-' => Self::NONE,
            '#' => Self::BOARD,
            _ => Self::BLOCK(input),
        }
    }
    fn is_none(&self) -> bool {
        match self {
            Obj::NONE => true,
            _ => false,
        }
    }
    fn is_block(&self) -> bool {
        match self {
            Obj::BLOCK(_) => true,
            _ => false,
        }
    }
    fn is_board(&self) -> bool {
        match self {
            Obj::BOARD => true,
            _ => false,
        }
    }
    fn get_char(&self) -> char {
        match self {
            Self::NONE => '-',
            Self::BOARD => '#',
            Self::BLOCK(c) => *c,
        }
    }
}

impl Board {
    fn new(input: &mut Input) -> Result<Self, Box<dyn Error>> {
        let scope = input
            .next_line()
            .split_whitespace()
            .map(|x| x.parse::<i32>())
            .collect::<Result<Vec<i32>, ParseIntError>>()?;
        let mut mapping: Vec<Vec<Obj>> = Vec::new();
        for _ in 0..scope[0] {
            let tmp = input
                .next_line()
                .split_whitespace()
                .map(|x| x.chars().nth(0).unwrap_or(' '))
                .collect::<Vec<char>>();

            let mut line: Vec<Obj> = Vec::new();
            for c in tmp {
                let next = Obj::new(c);
                line.push(next);
            }

            mapping.push(line);
        }

        Ok(Self {
            scope,
            mapping,
        })
    }

    fn moveto(&mut self, a: (i32, i32), b: (i32, i32)) {
        let tmp = Obj::new(mat!(self.mapping, a).get_char());
        mat!(self.mapping, a) = Obj::new(mat!(self.mapping, b).get_char());
        mat!(self.mapping, b) = tmp;
    }

    fn under_is_none(&self, coor: (i32, i32)) -> bool {
        let coor = (coor.0 + 1, coor.1);
        if self.in_scope(coor) {
            mat!(self.mapping, coor).is_none()
        } else {
            false
        }
    }

    fn combine(&mut self, format: [[i32; 2]; 4], coor: (i32, i32)) -> i32 {
        let mut to_remove: Vec<(i32, i32)> = Vec::new();
        let mut score = 0;
        for di in format {
            let cadidate: (i32, i32) = (coor.0 + di[0], coor.1 + di[1]);
            if self.in_scope(cadidate) {
                if mat!(self.mapping, coor).get_char() == mat!(self.mapping, cadidate).get_char() {
                    to_remove.push(cadidate);
                }
            }
        }
        if !to_remove.is_empty() {
            to_remove.push(coor);

            for r in to_remove {
                mat!(self.mapping, r) = Obj::NONE;
                score += 5;
            }
        }
        score
    }

    fn in_scope(&self, coor: (i32, i32)) -> bool {
        coor.0 < self.scope[0] && coor.1 < self.scope[1] && coor.0 >= 0 && coor.1 >= 0
    }
}

impl Operator {
    fn new(input: &mut Input) -> Result<Self, Box<dyn Error>> {
        let ques_amt = input.next_line().trim().parse::<usize>()?;
        let mut questions = Vec::<(i32, i32, char)>::new();

        for _ in 0..ques_amt {
            let mut token = input
                .next_line()
                .split_whitespace()
                .map(|x| x.to_string())
                .collect::<Vec<String>>()
                .into_iter();

            let (a, b, c) = (
                token.next().ok_or("a")?.parse::<i32>()?,
                token.next().ok_or("b")?.parse::<i32>()?,
                token.next().ok_or("c")?.chars().next().ok_or("empty c")?,
            );

            questions.push((a, b, c));
        }

        Ok(Self {
            questions,
            score: 0,
        })
    }

    fn solve(&mut self, board: &mut Board) {
        let check_direction = [
            [0, -1],
            [0, 1],
            [1, 0],
            [-1, 0],
        ];

        for (r, c, q) in &self.questions {
            let (r, c, q) = (*r, *c, *q);
            match mat!(board.mapping, (r, c)) {
                Obj::BLOCK(_) => {
                    let mut next = (r, c + (if q == 'L' { -1 } else { 1 }));
                    if !board.in_scope(next) {
                        self.score -= 5;
                        continue;
                    }

                    if mat!(board.mapping, next).is_board() {
                        self.score -= 5;
                    } else if mat!(board.mapping, next).is_none() {
                        next = fall(board, next);
                        board.moveto((r, c), next);
                        self.score += board.combine(check_direction, next);
                    }
                }
                _ => {
                    self.score -= 5;
                    continue;
                }
            }
            self.score += apply_gravity(board, check_direction);
        }
        print_board(&self.score, board);
    }
}

fn fall(board: &Board, coor: (i32, i32)) -> (i32, i32) {
    let mut current = coor;

    while board.under_is_none(current) {
        current.0 += 1;
    }

    current
}

fn apply_gravity(board: &mut Board, directions: [[i32; 2]; 4]) -> i32 {
    let mut score = 0;
    let mut total_changed = true;

    while total_changed {
        total_changed = false;
        let mut dropped_blocks = Vec::new();

        for r in (0..board.scope[0] - 1).rev() {
            for c in 0..board.scope[1] {
                let curr = (r, c);
                if mat!(board.mapping, curr).is_block() && board.under_is_none(curr) {
                    let next = fall(board, curr);
                    board.moveto(curr, next);
                    dropped_blocks.push(next);
                    total_changed = true;
                }
            }
        }

        let mut round_score = 0;
        for pos in dropped_blocks {
            round_score += board.combine(directions, pos);
        }

        score += round_score;

        if round_score == 0 && !total_changed {
            break;
        }
    }
    score
}

fn print_board(score: &i32, board: &Board) {
    println!("{}", score);
    for line in &board.mapping {
        let row_str: Vec<String> = line
            .iter()
            .map(|obj| obj.get_char().to_string())
            .collect();
        println!("{}", row_str.join(" "));
    }
}
