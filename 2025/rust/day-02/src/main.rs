use std::fs;

fn main() {
    let ranges = parse_input(&fs::read_to_string("../../inputs/02.txt").unwrap());

    println!("Sum1: {}", sum_of_invalid_ids(&ranges, is_mirrored_number));
    println!(
        "Sum2: {}",
        sum_of_invalid_ids(&ranges, is_repeating_pattern)
    );
}

fn parse_input(contents: &str) -> Vec<(u64, u64)> {
    contents
        .trim()
        .split(",")
        .map(|part: &str| {
            let (num1, num2) = part.split_once("-").unwrap();
            (num1.parse::<u64>().unwrap(), num2.parse::<u64>().unwrap())
        })
        .collect()
}

fn sum_of_invalid_ids(ranges: &[(u64, u64)], is_invalid: fn(u64) -> bool) -> u64 {
    let mut sum = 0;

    for (first, last) in ranges {
        for num in *first..=*last {
            if is_invalid(num) {
                sum += num;
            }
        }
    }

    sum
}

fn is_mirrored_number(num: u64) -> bool {
    let digits = number_of_digits(num);
    if !digits.is_multiple_of(2) {
        return false;
    }

    let divisor = 10_u64.pow((digits / 2) as u32);

    let left = num / divisor;
    let right = num % divisor;

    left == right
}

fn is_repeating_pattern(num: u64) -> bool {
    let digits = number_of_digits(num);
    if digits == 1 {
        return false;
    }

    let chunk_sizes = factorization(digits);

    for chunk_size in &chunk_sizes {
        let divisor = 10_u64.pow(*chunk_size as u32);
        let pattern = num % divisor;

        let mut remainder = num / divisor;
        let mut ok = true;

        let chunks_left: u64 = digits / chunk_size - 1;
        for _ in 0..chunks_left {
            if remainder % divisor != pattern {
                ok = false;
                break;
            }
            remainder /= divisor;
        }

        if ok {
            return true;
        }
    }

    false
}

fn number_of_digits(num: u64) -> u64 {
    (num.ilog10() as u64) + 1
}

fn factorization(num: u64) -> Vec<u64> {
    let primes = [2, 3, 5, 7];
    if primes.contains(&num) {
        return vec![1];
    }

    let mut factors = vec![];

    for factor in (2..=num / 2).rev() {
        if num.is_multiple_of(factor) && num != factor {
            factors.push(factor);
        }
    }

    factors
}

#[cfg(test)]
mod tests {
    use super::*;

    const TEST_INPUT: &str = "11-22,95-115,998-1012,1188511880-1188511890,222220-222224,1698522-1698528,446443-446449,38593856-38593862,565653-565659,824824821-824824827,2121212118-2121212124";

    #[test]
    fn test_part1() {
        assert_eq!(
            sum_of_invalid_ids(&parse_input(TEST_INPUT), is_mirrored_number),
            1227775554
        );
    }

    #[test]
    fn test_part2() {
        assert_eq!(
            sum_of_invalid_ids(&parse_input(TEST_INPUT), is_repeating_pattern),
            4174379265
        );
    }
}
