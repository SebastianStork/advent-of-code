use std::{
    collections::{hash_map::Entry, HashMap},
    fs,
};

fn main() {
    let (list1, list2) = read_input();

    println!("Total Distance: {}", get_total_distance(&list1, &list2));
    println!("Similarity Score: {}", get_similarity_score(&list1, &list2));
}

fn get_total_distance(list1: &Vec<u32>, list2: &Vec<u32>) -> u32 {
    let mut list = vec![];
    for (i, _) in list1.iter().enumerate() {
        list.push((list1[i], list2[i]));
    }

    list.iter().map(|x| x.0.abs_diff(x.1)).sum()
}

fn get_similarity_score(list1: &Vec<u32>, list2: &Vec<u32>) -> u32 {
    let mut scores = HashMap::new();

    for entry in list1 {
        scores.insert(entry, 0);
    }

    for entry in list2 {
        match scores.entry(entry) {
            Entry::Occupied(mut value) => {
                *value.get_mut() += 1;
            }
            Entry::Vacant(_) => (),
        }
    }

    scores.iter().map(|x| *x.0 * *x.1).sum()
}

fn read_input() -> (Vec<u32>, Vec<u32>) {
    let contents = fs::read_to_string("./input").unwrap();
    let lines = contents.lines();

    let mut list1 = vec![];
    let mut list2 = vec![];

    for line in lines {
        let parts: Vec<&str> = line.split("   ").collect();
        assert_eq!(parts.len(), 2);

        let num1: u32 = parts[0].parse().unwrap();
        let num2: u32 = parts[1].parse().unwrap();

        list1.push(num1);
        list2.push(num2);
    }

    list1.sort();
    list2.sort();

    (list1, list2)
}




// 9 8 7 6 5