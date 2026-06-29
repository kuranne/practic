use std::{ fmt::Display, str::FromStr };

pub struct BitMerge;

impl BitMerge {
    pub fn merge_form<T>(input: T) -> T
        where T: Display + FromStr, <T as FromStr>::Err: std::fmt::Debug
    {
        let mut ret = format!("{}", input);
        let input = ret.chars().collect::<Vec<char>>();

        if input.iter().any(|x| *x == '1') {
            ret = input
                .iter()
                .filter(|x| **x == '1')
                .collect::<String>();
        }

        ret.parse::<T>().expect("Can not parse String to T")
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn test_merge_from_string() {
        let input = String::from("1010101");
        let result = BitMerge::merge_form(input);
        assert_eq!(result, "1111")
    }

    #[test]
    fn test_merge_from_int() {
        let input = 1010101;
        let result = BitMerge::merge_form(input);
        assert_eq!(result, 1111)
    }

    #[test]
    fn test_merge_from_invalid() {
        let input = 1010101;
        let result = BitMerge::merge_form(input);
        assert_ne!(result, 11111);
    }

    #[test]
    #[should_panic]
    fn test_merge_panic() {
        BitMerge::merge_form::<i32>(0);
    }
}
