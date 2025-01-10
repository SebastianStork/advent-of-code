package main

import (
	"fmt"
	"log"
	"os"
	"strings"
)

func readInput() ([][]rune, error) {
	content, err := os.ReadFile("input")
	if err != nil {
		return nil, err
	}

	lines := strings.Split(strings.TrimSpace(string(content)), "\n")
	matrix := make([][]rune, len(lines))
	for i, line := range lines {
		matrix[i] = []rune(line)
	}

	return matrix, nil
}

func isXmas(word string) bool {
	return word == "XMAS" || word == "SAMX"
}

func isMas(word string) bool {
	return word == "MAS" || word == "SAM"
}

func countXmas(matrix [][]rune) int {
	rowCount := len(matrix)
	colCount := len(matrix[0])
	var count int

	for rowIndex := 0; rowIndex < rowCount; rowIndex++ {
		for colIndex := 0; colIndex < colCount; colIndex++ {
			words := [4]string{}

			// Horizontal word
			if colIndex < colCount-3 {
				words[0] = string(matrix[rowIndex][colIndex : colIndex+4])
			}

			// Vertical word
			if rowIndex < rowCount-3 {
				for i := 0; i <= 3; i++ {
					words[1] += string(matrix[rowIndex+i][colIndex])
				}
			}

			// Diagonal words
			if rowIndex < rowCount-3 && colIndex < colCount-3 {
				for i := 0; i <= 3; i++ {
					words[2] += string(matrix[rowIndex+i][colIndex+i])
					words[3] += string(matrix[rowIndex+(3-i)][colIndex+i])
				}
			}

			for _, word := range words {
				if isXmas(word) {
					count++
				}
			}
		}
	}

	return count
}

func countCrossMas(matrix [][]rune) int {
	rowCount := len(matrix)
	colCount := len(matrix[0])
	var count int

	for rowIndex := 0; rowIndex < rowCount-2; rowIndex++ {
		for colIndex := 0; colIndex < colCount-2; colIndex++ {
			var downDiagonalWord, upDiagonalWord string

			for i := 0; i <= 2; i++ {
				downDiagonalWord += string(matrix[rowIndex+i][colIndex+i])
				upDiagonalWord += string(matrix[rowIndex+(2-i)][colIndex+i])
			}

			if isMas(downDiagonalWord) && isMas(upDiagonalWord) {
				count++
			}
		}
	}

	return count
}

func main() {
	matrix, err := readInput()
	if err != nil {
		log.Fatalln(err)
	}

	// Part one
	fmt.Println("Number of XMAS occurrences:", countXmas(matrix))
	// Part two
	fmt.Println("Number of X-MAS occurrences:", countCrossMas(matrix))
}
