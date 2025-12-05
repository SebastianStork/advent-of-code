use std::fs;

struct Range {
    start: u64,
    end: u64,
}

impl Range {
    fn new(start: u64, end: u64) -> Range {
        Range { start, end }
    }

    fn contains(&self, num: u64) -> bool {
        num >= self.start && num <= self.end
    }

    fn expand(&mut self, overlap: &Range) {
        if overlap.start < self.start {
            self.start = overlap.start;
        }
        if overlap.end > self.end {
            self.end = overlap.end;
        }
    }
}

fn main() {
    let (ranges, available_ids) = parse_input(&fs::read_to_string("../../inputs/05.txt").unwrap());
    let ranges = compress(ranges);

    println!(
        "How many of the available ingredient IDs are fresh? {}",
        number_of_available_ids_in_rages(available_ids, ranges)
    );
}

fn parse_input(contents: &str) -> (Vec<Range>, Vec<u64>) {
    let (ranges, available_ids) = contents.trim().split_once("\n\n").unwrap();

    let ranges: Vec<Range> = ranges
        .lines()
        .map(|line| line.split_once("-").unwrap())
        .map(|(start, end)| Range::new(start.parse().unwrap(), end.parse().unwrap()))
        .collect();
    let available_ids: Vec<u64> = available_ids
        .lines()
        .map(|line| line.parse().unwrap())
        .collect();

    (ranges, available_ids)
}

fn compress(mut ranges: Vec<Range>) -> Vec<Range> {
    let mut compressed_ranges = vec![ranges.remove(0)];

    for range in ranges {
        let mut is_integrated = false;
        for compressed_range in &mut compressed_ranges {
            if compressed_range.contains(range.start) && compressed_range.contains(range.end) {
                is_integrated = true;
                break;
            }
            if compressed_range.contains(range.start) || compressed_range.contains(range.end) {
                compressed_range.expand(&range);
                is_integrated = true;
                break;
            }
        }
        if !is_integrated {
            compressed_ranges.push(range);
        }
    }

    compressed_ranges
}

fn number_of_available_ids_in_rages(available_ids: Vec<u64>, ranges: Vec<Range>) -> usize {
    available_ids
        .iter()
        .filter(|id| ranges.iter().any(|range| range.contains(**id)))
        .count()
}

#[cfg(test)]
mod tests {
    use super::*;

    const TEST_INPUT: &str = "
3-5
10-14
16-20
12-18

1
5
8
11
17
32
";

    #[test]
    fn test_part1() {
        let (ranges, available_ids) = parse_input(TEST_INPUT);
        let ranges = compress(ranges);

        assert_eq!(number_of_available_ids_in_rages(available_ids, ranges), 3);
    }
}
