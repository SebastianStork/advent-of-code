package main

import (
	"fmt"
	"log"
	"os"
	"slices"
	"strconv"
	"strings"
)

func main() {
	rules, updates, err := readInput()
	if err != nil {
		log.Fatalln(err)
	}

	correctSum, correctedSum := calculateMiddlePageSums(rules, updates)

	// Part one
	fmt.Println("Sum of correct middle pages:", correctSum)
	// Part two
	fmt.Println("Sum of corrected middle pages:", correctedSum)
}

func readInput() (rules map[int][]int, updates [][]int, err error) {
	content, err := os.ReadFile("input")
	if err != nil {
		return
	}

	lines := strings.Split(strings.TrimSpace(string(content)), "\n")
	rules = make(map[int][]int)

	isRules := true
	for _, line := range lines {
		if line == "" {
			isRules = false
			continue
		}

		if isRules {
			parts := strings.Split(line, "|")
			num1, _ := strconv.Atoi(parts[0])
			num2, _ := strconv.Atoi(parts[1])

			rules[num1] = append(rules[num1], num2)
		} else {
			parts := strings.Split(line, ",")
			var update []int

			for _, part := range parts {
				num, _ := strconv.Atoi(part)
				update = append(update, num)
			}

			updates = append(updates, update)
		}

	}

	return
}

func calculateMiddlePageSums(rules map[int][]int, updates [][]int) (correctSum, correctedSum int) {
	for _, update := range updates {
		if isCorrectlyOrdered(rules, update) {
			correctSum += middlePage(update)
		} else {
			correctedSum += middlePage(correctOrder(rules, update))
		}
	}

	return
}

func isCorrectlyOrdered(rules map[int][]int, pages []int) bool {
	return slices.IsSortedFunc(pages, comparePages(rules))
}

func correctOrder(rules map[int][]int, pages []int) []int {
	slices.SortFunc(pages, comparePages(rules))
	return pages
}

func comparePages(rules map[int][]int) func(int, int) int {
	return func(firstPage, secondPage int) int {
		for _, ruleNum := range rules[firstPage] {
			if secondPage == ruleNum {
				return -1
			}
		}

		return 1
	}
}

func middlePage(pages []int) int {
	return pages[len(pages)/2]
}
