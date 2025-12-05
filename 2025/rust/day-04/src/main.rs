use std::{cell::RefCell, fs, rc::Rc};

struct Roll {
    neighbours: Vec<Rc<RefCell<Roll>>>,
    deleted: bool,
}

impl Roll {
    fn new() -> Rc<RefCell<Roll>> {
        Rc::new(RefCell::new(Roll {
            neighbours: Vec::new(),
            deleted: false,
        }))
    }

    fn add_neighbour(this: &Rc<RefCell<Roll>>, neighbour: &Rc<RefCell<Roll>>) {
        this.borrow_mut().neighbours.push(Rc::clone(neighbour));
    }

    fn is_accessible(&self) -> bool {
        self.neighbours
            .iter()
            .filter(|neighbour| !neighbour.borrow().deleted)
            .count()
            < 4
    }

    fn delete(this: &Rc<RefCell<Roll>>) {
        if this.borrow().deleted {
            return;
        }

        this.borrow_mut().deleted = true;

        this.borrow()
            .neighbours
            .iter()
            .filter(|neighbour| !neighbour.borrow().deleted)
            .filter(|neighbour| neighbour.borrow().is_accessible())
            .for_each(Roll::delete);
    }
}

fn main() {
    let grid = parse_input(&fs::read_to_string("../../inputs/04.txt").unwrap());
    let rolls = build_graph(grid);

    println!(
        "Number of accessible rolls: {}",
        number_of_accessible_rolls(&rolls)
    );
    println!(
        "Number of removeable rolls: {}",
        number_of_removeable_rolls(&rolls)
    );
}

fn parse_input(contents: &str) -> Vec<Vec<Option<Rc<RefCell<Roll>>>>> {
    contents
        .trim()
        .lines()
        .map(|line: &str| {
            line.bytes()
                .map(|b| if b == b'@' { Some(Roll::new()) } else { None })
                .collect()
        })
        .collect()
}

fn build_graph(grid: Vec<Vec<Option<Rc<RefCell<Roll>>>>>) -> Vec<Rc<RefCell<Roll>>> {
    for (row_index, row) in grid.iter().enumerate() {
        for (col_index, cell) in row.iter().enumerate() {
            if let Some(roll) = cell {
                for neighbour in get_neighbours(&grid, row_index, col_index) {
                    Roll::add_neighbour(roll, neighbour);
                }
            }
        }
    }

    grid.into_iter().flatten().flatten().collect()
}

fn get_neighbours(
    grid: &[Vec<Option<Rc<RefCell<Roll>>>>],
    row: usize,
    col: usize,
) -> Vec<&Rc<RefCell<Roll>>> {
    let offsets = [
        (-1, -1),
        (-1, 0),
        (-1, 1),
        (0, -1),
        (0, 1),
        (1, -1),
        (1, 0),
        (1, 1),
    ];

    offsets
        .iter()
        .filter_map(|(di, dj)| {
            let (ni, nj) = (row as i32 + di, col as i32 + dj);
            grid.get(ni as usize)?.get(nj as usize)?.as_ref()
        })
        .collect()
}

fn number_of_accessible_rolls(rolls: &[Rc<RefCell<Roll>>]) -> usize {
    rolls
        .iter()
        .filter(|roll| roll.borrow().is_accessible())
        .count()
}

fn number_of_removeable_rolls(rolls: &[Rc<RefCell<Roll>>]) -> usize {
    rolls
        .iter()
        .filter(|roll| !roll.borrow().deleted)
        .filter(|roll| roll.borrow().is_accessible())
        .for_each(Roll::delete);

    rolls.iter().filter(|roll| roll.borrow().deleted).count()
}

#[cfg(test)]
mod tests {
    use super::*;

    const TEST_INPUT: &str = "
..@@.@@@@.
@@@.@.@.@@
@@@@@.@.@@
@.@@@@..@.
@@.@@@@.@@
.@@@@@@@.@
.@.@.@.@@@
@.@@@.@@@@
.@@@@@@@@.
@.@.@@@.@.
";

    #[test]
    fn test_part1() {
        assert_eq!(
            number_of_accessible_rolls(&build_graph(parse_input(TEST_INPUT))),
            13
        );
    }

    #[test]
    fn test_part2() {
        assert_eq!(
            number_of_removeable_rolls(&build_graph(parse_input(TEST_INPUT))),
            43
        );
    }
}
