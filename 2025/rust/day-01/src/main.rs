use std::fs::{self};

const STARTING_POSITION: i32 = 50;
const DIAL_RANGE: i32 = 100;

fn main() {
    let rotations = read_rotations();

    println!("Password1: {}", count_zero_positions(&rotations));
    println!("Password2: {}", count_zero_clicks(&rotations));
}

fn read_rotations() -> Vec<i32> {
    fs::read_to_string("../../inputs/01.txt")
        .unwrap()
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
