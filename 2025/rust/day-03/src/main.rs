use std::fs;

fn main() {
    let banks = parse_input(&fs::read_to_string("../../inputs/03.txt").unwrap());

    println!("Total output joltage: {}", total_joltage(banks));
}

fn parse_input(contents: &str) -> Vec<Vec<u8>> {
    contents
        .trim()
        .lines()
        .map(|line: &str| line.bytes().map(|b| b - b'0').collect())
        .collect()
}

fn total_joltage(banks: Vec<Vec<u8>>) -> u32 {
    banks.iter().map(|bank| largest_joltage(bank)).sum()
}

fn largest_joltage(batteries: &[u8]) -> u32 {
    let mut first = batteries[0];
    let mut second = batteries[1];

    for i in 1..batteries.len() - 1 {
        if batteries[i] > first {
            first = batteries[i];
            second = batteries[i + 1];
        } else if batteries[i + 1] > second {
            second = batteries[i + 1];
        }
    }

    (first * 10 + second) as u32
}

#[cfg(test)]
mod tests {
    use super::*;

    const TEST_INPUT: &str = "987654321111111
811111111111119
234234234234278
818181911112111
";

    #[test]
    fn test_part1() {
        assert_eq!(total_joltage(parse_input(TEST_INPUT)), 357);
    }
}
