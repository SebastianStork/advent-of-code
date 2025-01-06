package main

import (
	"fmt"
	"log"
	"os"
	"sort"
	"strconv"
	"strings"
)

func readInput() (leftList, rightList []int, err error) {
	content, err := os.ReadFile("input")
	if err != nil {
		return
	}

	lines := strings.Split(strings.TrimSpace(string(content)), "\n")
	for _, line := range lines {
		parts := strings.Fields(line)

		leftNum, _ := strconv.Atoi(parts[0]) // ignore error because input is always correct
		rightNum, _ := strconv.Atoi(parts[1])

		leftList = append(leftList, leftNum)
		rightList = append(rightList, rightNum)
	}

	sort.Ints(leftList)
	sort.Ints(rightList)

	return
}

func totalDistance(leftList, rightList []int) (totalDistance int) {
	for i := range leftList {
		difference := leftList[i] - rightList[i]
		if difference < 0 {
			difference = -difference
		}

		totalDistance += difference
	}

	return
}

func similarityScore(leftList, rightList []int) (similarityScore int) {
	rightMap := make(map[int]int)

	for _, number := range rightList {
		rightMap[number]++
	}

	for _, number := range leftList {
		similarityScore += number * rightMap[number]
	}

	return
}

func main() {
	leftList, rightList, err := readInput()
	if err != nil {
		log.Fatalln(err)
	}

	// Part one
	fmt.Println("Total distance:", totalDistance(leftList, rightList))

	// Part two
	fmt.Println("Similarity Score:", similarityScore(leftList, rightList))
}
