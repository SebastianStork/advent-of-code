package main

import (
	"fmt"
	"log"
	"os"
	"strings"
)

type position struct {
	row int
	col int
}

type state struct {
	row       int
	col       int
	direction int
}

const (
	up    = 0
	right = 1
	down  = 2
	left  = 3
)

func readInput() (area [][]rune, start state, err error) {
	content, err := os.ReadFile("input")
	if err != nil {
		return
	}

	lines := strings.Split(strings.TrimSpace(string(content)), "\n")
	area = make([][]rune, len(lines))

	for rowIndex, line := range lines {
		for colIndex, symbol := range line {
			if symbol == '^' {
				start = state{row: rowIndex, col: colIndex, direction: up}
			}
		}

		area[rowIndex] = []rune(line)
	}

	return
}

func stateToPos(s state) position {
	return position{s.row, s.col}
}

func isOutOfBounds(area [][]rune, pos position) bool {
	return (pos.row < 0 || pos.row >= len(area)) || (pos.col < 0 || pos.col >= len(area[0]))
}

func isObstacle(area [][]rune, pos position) bool {
	return area[pos.row][pos.col] == '#'
}

func takeStep(area [][]rune, currentState state) (bool, state) {
	directions := map[int]position{up: {-1, 0}, right: {0, 1}, down: {1, 0}, left: {0, -1}}

	newState := state{
		row:       currentState.row + directions[currentState.direction].row,
		col:       currentState.col + directions[currentState.direction].col,
		direction: currentState.direction,
	}

	if isOutOfBounds(area, stateToPos(newState)) {
		return false, newState
	}

	if isObstacle(area, stateToPos(newState)) {
		currentState.direction = (currentState.direction + 1) % 4
		return true, currentState
	}

	return true, newState
}

func findDistinctPositions(area [][]rune, currentState state) map[position]bool {
	distinctPositions := make(map[position]bool)

	for ok := true; ok; {
		distinctPositions[stateToPos(currentState)] = true

		ok, currentState = takeStep(area, currentState)
	}

	return distinctPositions
}

func isLoopCausingObstruction(area [][]rune, currentState state) bool {
	path := make(map[state]bool)

	for ok := true; ok; {
		if _, isLoop := path[currentState]; isLoop {
			return true
		}
		path[currentState] = true

		ok, currentState = takeStep(area, currentState)
	}

	return false
}

func findLoopCausingObstructions(area [][]rune, start state, distinctPositions map[position]bool) []position {
	var loopObstructions []position

	for obstaclePos := range distinctPositions {
		if obstaclePos == stateToPos(start) {
			continue
		}

		area[obstaclePos.row][obstaclePos.col] = '#'
		if isLoopCausingObstruction(area, start) {
			loopObstructions = append(loopObstructions, obstaclePos)
		}
		area[obstaclePos.row][obstaclePos.col] = '.'
	}

	return loopObstructions
}

func main() {
	area, start, err := readInput()
	if err != nil {
		log.Fatalln(err)
	}

	distinctPositions := findDistinctPositions(area, start)
	loopObstructions := findLoopCausingObstructions(area, start, distinctPositions)

	// Part one
	fmt.Println("Number of distinct positions:", len(distinctPositions))
	// Part two
	fmt.Println("Number of potential obstructions:", len(loopObstructions))
}
