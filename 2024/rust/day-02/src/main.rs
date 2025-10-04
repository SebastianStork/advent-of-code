use std::fs;

fn main() {
    let reports = read_input();

    let helper: Vec<bool> = reports
        .iter()
        .map(|report| check_safety(report, false))
        .collect();

    dbg!(helper);

    let safety_score: u16 = reports
        .iter()
        .map(|report| check_safety(report, false))
        .map(|is_safe| is_safe as u16)
        .sum();

    dbg!(safety_score);
}

fn read_input() -> Vec<Vec<u8>> {
    let contents = fs::read_to_string("./input").unwrap();

    let line_to_levels = |line: &str| {
        line.split(" ")
            .map(|level| level.parse::<u8>().unwrap())
            .collect()
    };

    contents.lines().map(line_to_levels).collect()
}

fn check_safety(report: &Vec<u8>, is_dampened: bool) -> bool {
    let result =
        is_strictly_increasing(report, is_dampened) || is_strictly_decreasing(report, is_dampened);
    if is_dampened {
        //dbg!(report, result);
    }
    result
}

fn try_dampening(index: usize, report: &Vec<u8>) -> bool {
    let mut temp_report = report.clone();
    temp_report.remove(index);
    if check_safety(&temp_report, true) {
        return true;
    }

    let mut temp_report = report.clone();
    temp_report.remove(index - 1);
    if check_safety(&temp_report, true) {
        return true;
    }

    if index + 1 < report.len() {
        let mut temp_report = report.clone();
        temp_report.remove(index + 1);
        return check_safety(&temp_report, true);
    }

    false
}

fn is_strictly_increasing(report: &Vec<u8>, is_dampened: bool) -> bool {
    for i in 1..report.len() {
        if report[i - 1] >= report[i] {
            if is_dampened {
                return false;
            }
            return try_dampening(i, report);
        }

        let distance = report[i].abs_diff(report[i - 1]);
        if distance > 3 {
            if is_dampened {
                return false;
            }
            return try_dampening(i, report);
        }
    }

    true
}

fn is_strictly_decreasing(report: &Vec<u8>, is_dampened: bool) -> bool {
    for i in 1..report.len() {
        if report[i - 1] <= report[i] {
            if is_dampened {
                return false;
            }
            return try_dampening(i, report);
        }

        let distance = report[i].abs_diff(report[i - 1]);
        if distance > 3 {
            if is_dampened {
                return false;
            }
            return try_dampening(i, report);
        }
    }

    true
}
