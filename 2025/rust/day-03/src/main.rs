use std::fs;

fn main() {
    let banks = parse_input(&fs::read_to_string("../../inputs/03.txt").unwrap());

    println!("Total output joltage: {}", total_joltage(&banks, 2));
    println!("New total output joltage: {}", total_joltage(&banks, 12));
}

fn parse_input(contents: &str) -> Vec<Vec<u8>> {
    contents
        .trim()
        .lines()
        .map(|line: &str| line.bytes().map(|b| b - b'0').collect())
        .collect()
}

fn total_joltage(banks: &[Vec<u8>], number_of_activate_batteries: usize) -> u64 {
    banks
        .iter()
        .map(|bank| largest_joltage(bank, number_of_activate_batteries))
        .sum()
}

fn largest_joltage(batteries: &[u8], number_of_activate_batteries: usize) -> u64 {
    let mut active_batteries: Vec<u8> = batteries[0..number_of_activate_batteries].into();

    for i in 1..batteries.len() - (number_of_activate_batteries - 1) {
        for j in 0..number_of_activate_batteries {
            if batteries[j + i] > active_batteries[j] {
                active_batteries[j..number_of_activate_batteries]
                    .copy_from_slice(&batteries[j + i..number_of_activate_batteries + i]);
            }
        }
    }

    active_batteries
        .iter()
        .rev()
        .enumerate()
        .map(|(i, joltage)| *joltage as u64 * 10_u64.pow(i as u32))
        .sum()
}

#[cfg(test)]
mod tests {
    use super::*;

    const TEST_INPUT: &str = "987654321111111
811111111111119
234234234234278
818181911112111";

    #[test]
    fn test_part1() {
        assert_eq!(total_joltage(&parse_input(TEST_INPUT), 2), 357);
    }

    #[test]
    fn test_part2() {
        assert_eq!(total_joltage(&parse_input(TEST_INPUT), 12), 3121910778619);
    }
}
