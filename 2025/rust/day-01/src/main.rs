use std::fs::{self};

fn main() {
    let rotations = read_input();

    println!("Password: {}", count_neutral_positions(rotations));
}

fn read_input() -> Vec<i32> {
    let contents = fs::read_to_string("../../inputs/01.txt").unwrap();
    let lines = contents.lines();

    let mut rotations = vec![];

    for line in lines {
        let (direction, distance) = line.split_at(1);

        let distance = distance.parse::<i32>().unwrap();

        let rotation = match direction {
            "L" => distance * -1,
            "R" => distance,
            _ => panic!(),
        };

        rotations.push(rotation);
    }

    rotations
}

fn count_neutral_positions(rotations: Vec<i32>) -> i32 {
    let mut counter = 0;
    let mut position = 50;

    for rotation in rotations {
        position = (position + rotation) % 100;

        if position == 0 {
            counter += 1;
        }
    }

    counter
}
