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

func readInput() (topographicMap [][]int, trailheads []position, err error) {
	content, err := os.ReadFile("input")
	if err != nil {
		return
	}

	lines := strings.Split(strings.TrimSpace(string(content)), "\n")

	topographicMap = make([][]int, len(lines))
	for i := range topographicMap {
		topographicMap[i] = make([]int, len(lines[i]))
	}

	for rowIndex := range lines {
		for colIndex := range topographicMap[rowIndex] {
			topographicMap[rowIndex][colIndex] = int(lines[rowIndex][colIndex]) - '0'

			if topographicMap[rowIndex][colIndex] == 0 {
				trailheads = append(trailheads, position{rowIndex, colIndex})
			}
		}
	}

	return
}

func developTrails(topographicMap [][]int, trailheads []position) (trails map[position][]map[position][]position) {
	trails = make(map[position][]map[position][]position)

	for _, trailhead := range trailheads {
		trails[trailhead] = make([]map[position][]position, 10)
		trails[trailhead][0] = make(map[position][]position)
		trails[trailhead][0][trailhead] = nil
	}

	for _, trailheadTrails := range trails {
		for height := 0; height < 9; height++ {
			trailheadTrails[height+1] = make(map[position][]position)

			for pos := range trailheadTrails[height] {
				possibleSteps := []int{-1, 1}
				for _, i := range possibleSteps {
					newRow := pos.row + i
					if newRow >= 0 && newRow < len(topographicMap) {
						if topographicMap[newRow][pos.col] == height+1 {
							trailheadTrails[height+1][position{newRow, pos.col}] = append(trailheadTrails[height+1][position{newRow, pos.col}], pos)
						}
					}

					newCol := pos.col + i
					if newCol >= 0 && newCol < len(topographicMap[pos.row]) {
						if topographicMap[pos.row][newCol] == height+1 {
							trailheadTrails[height+1][position{pos.row, newCol}] = append(trailheadTrails[height+1][position{newRow, pos.col}], pos)
						}
					}
				}
			}
		}
	}

	return
}

func scoreSum(trails map[position][]map[position][]position) int {
	var sum int
	for _, trailheadTrails := range trails {
		for _ = range trailheadTrails[9] {
			sum++
		}
	}
	return sum
}

func main() {
	topographicMap, trailheads, err := readInput()
	if err != nil {
		log.Fatalln(err)
	}

	trails := developTrails(topographicMap, trailheads)

	fmt.Println("Sum of the scores of all trailheads:", scoreSum(trails))
}
