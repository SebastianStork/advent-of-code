use std::fs;

struct Range {
    start: u64,
    end: u64,
}

impl Range {
    fn new(start: u64, end: u64) -> Self {
        Range { start, end }
    }

    fn contains(&self, num: u64) -> bool {
        num >= self.start && num <= self.end
    }

    fn overlaps(&self, other: &Range) -> bool {
        self.contains(other.start) || self.contains(other.end)
    }

    fn merge_with(&mut self, overlap: &Range) {
        if overlap.start < self.start {
            self.start = overlap.start;
        }
        if overlap.end > self.end {
            self.end = overlap.end;
        }
    }

    fn length(&self) -> u64 {
        self.end - self.start + 1
    }
}

fn main() {
    let (ranges, available_ids) = parse_input(&fs::read_to_string("../../inputs/05.txt").unwrap());
    let ranges = merge_overlapping_ranges(ranges);

    println!(
        "Number of available IDs in ranges: {}",
        count_available_ids_in_ranges(available_ids, &ranges)
    );
    println!("Number of IDs in ranges: {}", count_ids_in_ranges(&ranges));
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

fn merge_overlapping_ranges(mut ranges: Vec<Range>) -> Vec<Range> {
    ranges.sort_by_key(|range| range.start);

    let mut compressed_ranges = vec![ranges.remove(0)];

    for range in ranges {
        let previous = compressed_ranges.last_mut().unwrap();

        if previous.overlaps(&range) {
            previous.merge_with(&range);
        } else {
            compressed_ranges.push(range);
        }
    }

    compressed_ranges
}

fn count_available_ids_in_ranges(available_ids: Vec<u64>, ranges: &[Range]) -> usize {
    available_ids
        .iter()
        .filter(|id| ranges.iter().any(|range| range.contains(**id)))
        .count()
}

fn count_ids_in_ranges(ranges: &[Range]) -> u64 {
    ranges.iter().map(|range| range.length()).sum()
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
        let ranges = merge_overlapping_ranges(ranges);

        assert_eq!(count_available_ids_in_ranges(available_ids, &ranges), 3);
    }

    #[test]
    fn test_part2() {
        let (ranges, _) = parse_input(TEST_INPUT);
        let ranges = merge_overlapping_ranges(merge_overlapping_ranges(ranges));

        assert_eq!(count_ids_in_ranges(&ranges), 14);
    }
}
