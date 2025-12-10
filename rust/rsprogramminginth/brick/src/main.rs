use std::io;

fn input() -> String {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    input.trim().to_string()
}
fn main() {
    let rc: Vec<usize> = input()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();

    let mut mapping: Vec<Vec<char>> = Vec::new();
    let mut horizon_map: Vec<Vec<bool>> = vec![vec![false; rc[0]]; rc[1]];
    for i in 0..rc[0] {
        mapping.push(input().chars().collect());
        for j in 0..rc[1] {
            horizon_map[j][i] = if mapping[i][j] == '.' { false } else { true };
        }
    }

    let bricks: Vec<usize> = input()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();

    for i in 0..rc[1] {
        for _ in 0..bricks[i] {
            for j in 0..rc[0] {
                if horizon_map[i][0] {
                    break;
                }
                
                if horizon_map[i][j] && j > 0 {
                    horizon_map[i][j-1] = true;
                    mapping[j - 1][i] = '#';
                    break;
                } else if j == rc[0] - 1 && !horizon_map[i][j] {
                    horizon_map[i][j] = true;
                    mapping[j][i] = '#';
                    break;
                }
            }
        }
    }

    for p in &mapping{
        println!("{}", p.iter().collect::<String>());
    }
}
