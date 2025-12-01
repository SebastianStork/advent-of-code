use std::fs::{self};

fn main() {
    let rotations = read_rotations();

    println!("Password1: {}", count_zero_positions(&rotations));
    println!("Password2: {}", count_zero_clicks(&rotations));
}

fn read_rotations() -> Vec<i32> {
    let contents = fs::read_to_string("../../inputs/01.txt").unwrap();
    let lines = contents.lines();

    let mut rotations = vec![];

    for line in lines {
        let (direction, distance) = line.split_at(1);

        let distance = distance.parse::<i32>().unwrap();

        let rotation = match direction {
            "L" => -distance,
            "R" => distance,
            _ => panic!(),
        };

        rotations.push(rotation);
    }

    rotations
}

fn count_zero_positions(rotations: &Vec<i32>) -> i32 {
    let mut counter = 0;
    let mut position = 50;

    for rotation in rotations {
        position = (position + rotation).rem_euclid(100);

        if position == 0 {
            counter += 1;
        }
    }

    counter
}

fn count_zero_clicks(rotations: &Vec<i32>) -> i32 {
    let mut counter = 0;
    let mut position = 50;

    for rotation in rotations {
        position += rotation;

        counter += (position / 100).abs();
        if position < 0 && position != *rotation {
            counter += 1;
        }
        if position == 0 {
            counter += 1;
        }

        position = position.rem_euclid(100);
    }

    counter
}
