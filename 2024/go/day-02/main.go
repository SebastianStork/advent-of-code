package main

import (
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
)

func readInput() ([][]int, error) {
	content, err := os.ReadFile("input")
	if err != nil {
		return nil, err
	}

	lines := strings.Split(strings.TrimSpace(string(content)), "\n")
	var reports [][]int

	for _, line := range lines {
		parts := strings.Fields(line)
		levels := make([]int, len(parts))

		for i, part := range parts {
			levels[i], _ = strconv.Atoi(part)
		}

		reports = append(reports, levels)
	}

	return reports, nil
}

func isSafeReport(levels []int) (bool, int) {
	isIncreasing := levels[0] < levels[len(levels)-1]

	for i := 1; i < len(levels); i++ {
		diff := levels[i] - levels[i-1]

		if (isIncreasing && (diff <= 0 || diff > 3)) || (!isIncreasing && (diff >= 0 || diff < -3)) {
			return false, i
		}
	}

	return true, -1
}

func countSafeReports(reports [][]int) int {
	var count int

	for _, levels := range reports {
		isSafe, _ := isSafeReport(levels)
		if isSafe {
			count++
		}
	}

	return count
}

func countDampenedSafeReports(reports [][]int) int {
	var count int

	for _, levels := range reports {
		isSafe, unsafeIndex := isSafeReport(levels)
		if isSafe {
			count++
			continue
		}

		for i := unsafeIndex; i >= unsafeIndex-1 && i >= 0; i-- {
			var dampenedLevels []int
			dampenedLevels = append(dampenedLevels, levels[:i]...)
			dampenedLevels = append(dampenedLevels, levels[i+1:]...)

			isSafe, _ = isSafeReport(dampenedLevels)
			if isSafe {
				count++
				break
			}
		}
	}

	return count
}

func main() {
	reports, err := readInput()
	if err != nil {
		log.Fatalln(err)
	}

	// Part one
	fmt.Println("Number of safe reports:", countSafeReports(reports))
	// Part two
	fmt.Println("Number of dampened safe reports:", countDampenedSafeReports(reports))
}
