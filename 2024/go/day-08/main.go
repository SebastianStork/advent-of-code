package main

import (
	"fmt"
	"log"
	"os"
	"strings"
)

type position struct {
	row, col int
}

func readInput() (antennas map[rune][]position, dimensions position, err error) {
	content, err := os.ReadFile("input")
	if err != nil {
		return
	}

	lines := strings.Split(strings.TrimSpace(string(content)), "\n")
	antennas = make(map[rune][]position)

	for rowIndex, line := range lines {
		for colIndex, frequency := range line {
			if frequency != '.' {
				antennas[frequency] = append(antennas[frequency], position{row: rowIndex, col: colIndex})
			}
		}
	}

	dimensions = position{row: len(lines), col: len(lines[0])}

	return
}

func isInBounds(antinode, dimensions position) bool {
	return (antinode.row >= 0 && antinode.row < dimensions.row) && (antinode.col >= 0 && antinode.col < dimensions.col)
}

func deltaVector(antenna1, antenna2 position) position {
	return position{
		row: antenna2.row - antenna1.row,
		col: antenna2.col - antenna1.col,
	}
}

func antennaPairAntinodes(antenna1, antenna2, dimensions position) []position {
	deltaVector := deltaVector(antenna1, antenna2)

	antinode1 := position{
		row: antenna1.row - deltaVector.row,
		col: antenna1.col - deltaVector.col,
	}
	antinode2 := position{
		row: antenna2.row + deltaVector.row,
		col: antenna2.col + deltaVector.col,
	}

	var antinodes []position
	if isInBounds(antinode1, dimensions) {
		antinodes = append(antinodes, antinode1)
	}
	if isInBounds(antinode2, dimensions) {
		antinodes = append(antinodes, antinode2)
	}

	return antinodes
}

func antennaPairResonantAntinodes(antenna1, antenna2, dimensions position) []position {
	var resonantAntinodes []position
	deltaVector := deltaVector(antenna1, antenna2)

	// Resonant antinodes
	antinode1 := antenna1
	for isInBounds(antinode1, dimensions) {
		resonantAntinodes = append(resonantAntinodes, antinode1)

		antinode1.row -= deltaVector.row
		antinode1.col -= deltaVector.col
	}

	antinode2 := antenna2
	for isInBounds(antinode2, dimensions) {
		resonantAntinodes = append(resonantAntinodes, antinode2)

		antinode2.row += deltaVector.row
		antinode2.col += deltaVector.col
	}

	return resonantAntinodes
}

func findAllAntinodes(antennas map[rune][]position, dimensions position) (uniqueAntinodes, uniqueResonantAntinodes map[position]struct{}) {
	uniqueAntinodes = make(map[position]struct{})
	uniqueResonantAntinodes = make(map[position]struct{})

	for _, frequencyGroup := range antennas {
		for antenna1Index := 0; antenna1Index < len(frequencyGroup)-1; antenna1Index++ {
			for antenna2Index := antenna1Index + 1; antenna2Index < len(frequencyGroup); antenna2Index++ {
				antenna1 := frequencyGroup[antenna1Index]
				antenna2 := frequencyGroup[antenna2Index]

				foundAntinodes := antennaPairAntinodes(antenna1, antenna2, dimensions)
				foundResonantAntinodes := antennaPairResonantAntinodes(antenna1, antenna2, dimensions)

				for _, antinode := range foundAntinodes {
					uniqueAntinodes[antinode] = struct{}{}
				}

				for _, antinode := range foundResonantAntinodes {
					uniqueResonantAntinodes[antinode] = struct{}{}
				}
			}
		}
	}

	return
}

func main() {
	antennas, dimensions, err := readInput()
	if err != nil {
		log.Fatalln(err)
	}

	uniqueAntinodes, uniqueResonantAntinodes := findAllAntinodes(antennas, dimensions)

	// Part one
	fmt.Println("Number of unique antinodes:", len(uniqueAntinodes))
	// Part two
	fmt.Println("Number of unique antinodes when taking resonant harmonics into account:", len(uniqueResonantAntinodes))
}
