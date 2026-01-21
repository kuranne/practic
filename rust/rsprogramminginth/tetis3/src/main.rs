// surrended to pre suffix array ;<
use std::io::{self, BufRead};

fn input(stdin: &mut impl BufRead, buf: &mut String) {
    buf.clear();
    stdin.read_line(buf).unwrap();
}

fn sffx_arry(b: &[i128], n: usize) -> (Vec<usize>, Vec<usize>) {
    // sort & add a 0
    let mut vec: Vec<i128> = b.to_vec();
    vec.sort_unstable();
    vec.dedup();
    
    // compressed
    let mut compressed = vec![0usize; n];
    for i in 0..n {
        compressed[i] = vec.binary_search(&b[i]).unwrap();
    }
    
    // map
    let mut cnt = vec![0usize; n + 1];
    for &val in &compressed {
        cnt[val] += 1;
    }
    for i in 1..n {
        cnt[i] += cnt[i - 1];
    }
    let mut p = vec![0usize; n];
    for i in (0..n).rev() {
        cnt[compressed[i]] -= 1;
        p[cnt[compressed[i]]] = i;
    }
    let mut c = vec![0usize; n];
    c[p[0]] = 0;
    let mut ord = 1;
    for i in 1..n {
        if compressed[p[i - 1]] != compressed[p[i]] {
            ord += 1;
        }
        c[p[i]] = ord - 1;
    }
    let mut h = 0;

    while (1 << h) < n {
        let mut pn = vec![0usize; n];
        for i in 0..n {
            pn[i] = if p[i] >= (1 << h) { 
                p[i] - (1 << h) 
            } else { 
                p[i] + n - (1 << h) 
            };
        }
        
        let mut cnt = vec![0usize; n];
        for &val in &c {
            cnt[val] += 1;
        }
        for i in 1..n {
            cnt[i] += cnt[i - 1];
        }
        
        for i in (0..n).rev() {
            cnt[c[pn[i]]] -= 1;
            p[cnt[c[pn[i]]]] = pn[i];
        }
        
        let mut cn = vec![0usize; n];
        cn[p[0]] = 0;
        ord = 1;
        for i in 1..n {
            let curn = (c[p[i]], c[(p[i] + (1 << h)) % n]);
            let prev = (c[p[i - 1]], c[(p[i - 1] + (1 << h)) % n]);
            if curn != prev {
                ord += 1;
            }
            cn[p[i]] = ord - 1;
        }
        c = cn;
        h += 1;
    }
    
    (p, c)
}

fn check_gap(col: &[i128], mapcol: &[i128], p: &[usize], d: &[i128]) -> i32 {
    
    // a, b, size, prev return int
    let n = mapcol.len();
    let col_len = col[0] as usize;
    
    if col_len <= 1 {
        return n as i32;
    }
    
    let s = col_len - 1;
    let mut vv = vec![0i128; s];
    for i in 0..s {
        vv[i] = col[i + 1] - col[i + 2];
    }
    
    let mut ch = true;
    // chk frmt
    for i in 0..s {
        if i + p[n - 1] >= n {
            ch = false;
            break;
        }
        if vv[i] < d[p[n - 1] + i] {
            break;
        }
        if vv[i] > d[p[n - 1] + i] {
            ch = false;
            break;
        }
    }
    if !ch {
        return 0;
    }
    
    let mut l = 0;
    let mut r = n - 1;
    // 
    while l < r {
        let m = (l + r) >> 1;
        let mut ch2 = true;
        for i in 0..s {
            if i + p[m] >= n {
                ch2 = false;
                break;
            }
            if vv[i] < d[p[m] + i] {
                break;
            }
            if vv[i] > d[p[m] + i] {
                ch2 = false;
                break;
            }
        }
        if ch2 {
            r = m;
        } else {
            l = m + 1;
        }
    }
    let le = l;
    
    l = 0;
    r = n - 1;
    while l < r {
        let m = (l + r + 1) >> 1;
        let mut ch2 = false;
        for i in 0..s {
            if i + p[m] >= n {
                ch2 = false;
                break;
            }
            if vv[i] < d[p[m] + i] {
                ch2 = true;
                break;
            }
            if vv[i] > d[p[m] + i] {
                ch2 = false;
                break;
            }
        }
        if ch2 {
            r = m - 1;
        } else {
            l = m;
        }
    }
    
    (r - le + 1) as i32
}

fn main() {
    let stdin = io::stdin();
    let mut stdin = stdin.lock();
    let mut buf = String::with_capacity(1024);
    
    input(&mut stdin, &mut buf);
    let _tcol: usize = buf.trim().parse().unwrap();
    
    input(&mut stdin, &mut buf);
    let mapcol: Vec<i128> = buf
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();
    
    let n = mapcol.len();
    
    let mut b = vec![0i128; n];
    let mut d = vec![0i128; n];
    for i in 0..n - 1 {
        b[i] = mapcol[i + 1] - mapcol[i];
        d[i] = b[i];
    }
    b[n - 1] = -2_000_000_000_000_000_000i128;
    d[n - 1] = b[n - 1];
    
    let (p, _c) = sffx_arry(&b, n);
    
    input(&mut stdin, &mut buf);
    let qnums: usize = buf.trim().parse().unwrap();
    
    
    for _ in 0..qnums {
        input(&mut stdin, &mut buf);
        let col: Vec<i128> = buf
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect();
        
        println!("{}", check_gap(&col, &mapcol, &p, &d));
    }
}