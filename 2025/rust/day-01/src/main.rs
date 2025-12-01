use std::fs::{self};

const STARTING_POSITION: i32 = 50;
const DIAL_RANGE: i32 = 100;

fn main() {
    let rotations = parse_rotations(&fs::read_to_string("../../inputs/01.txt").unwrap());

    println!("Password1: {}", count_zero_positions(&rotations));
    println!("Password2: {}", count_zero_clicks(&rotations));
}

fn parse_rotations(contents: &str) -> Vec<i32> {
    contents
        .lines()
        .map(|line| {
            let distance = line[1..].parse::<i32>().unwrap();
            if line.starts_with('L') {
                -distance
            } else {
                distance
            }
        })
        .collect()
}

fn count_zero_positions(rotations: &[i32]) -> i32 {
    let mut counter = 0;
    let mut position = STARTING_POSITION;

    for rotation in rotations {
        position = (position + rotation).rem_euclid(DIAL_RANGE);

        if position == 0 {
            counter += 1;
        }
    }

    counter
}

fn count_zero_clicks(rotations: &[i32]) -> i32 {
    let mut counter = 0;
    let mut position = STARTING_POSITION;

    for rotation in rotations {
        position += rotation;

        counter += (position / DIAL_RANGE).abs();
        if position < 0 && position != *rotation {
            counter += 1;
        }
        if position == 0 {
            counter += 1;
        }

        position = position.rem_euclid(DIAL_RANGE);
    }

    counter
}

#[cfg(test)]
mod tests {
    use super::*;

    const TEST_INPUT: &str = "L68
L30
R48
L5
R60
L55
L1
L99
R14
L82";

    #[test]
    fn test_part1() {
        assert_eq!(count_zero_positions(&parse_rotations(TEST_INPUT)), 3);
    }

    #[test]
    fn test_part2() {
        assert_eq!(count_zero_clicks(&parse_rotations(TEST_INPUT)), 6);
    }
}
