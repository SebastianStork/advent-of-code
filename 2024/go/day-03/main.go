package main

import (
	"fmt"
	"log"
	"os"
	"regexp"
	"strconv"
)

func readInput() (string, error) {
	content, err := os.ReadFile("input")
	if err != nil {
		return "", err
	}

	return string(content), nil
}

func instructionsResult(memory string) (int, int) {
	regex := regexp.MustCompile(`mul\((\d{1,3}),(\d{1,3})\)|do\(\)|don't\(\)`)
	matches := regex.FindAllStringSubmatch(memory, -1)
	var totalSum, conditionalSum int

	do := true
	for _, match := range matches {
		switch match[0] {
		case "do()":
			do = true
		case "don't()":
			do = false
		default:
			num1, _ := strconv.Atoi(match[1])
			num2, _ := strconv.Atoi(match[2])

			totalSum += num1 * num2
			if do {
				conditionalSum += num1 * num2
			}
		}
	}

	return totalSum, conditionalSum
}

func main() {
	memory, err := readInput()
	if err != nil {
		log.Fatalln(err)
	}

	totalSum, conditionalSum := instructionsResult(memory)

	// Part one
	fmt.Println("Sum of the instructions:", totalSum)
	// Part two
	fmt.Println("Sum of the instructions but with conditionals:", conditionalSum)
}
