package main

import (
	"fmt"
	"log"
	"os"
	"slices"
	"strings"
)

func readInput() (fileMap []int, err error) {
	content, err := os.ReadFile("input")
	if err != nil {
		return
	}

	line := strings.TrimSpace(string(content))
	for _, digit := range line {
		fileMap = append(fileMap, int(digit-'0'))
	}

	return
}

func convertToBlockMap(fileMap []int) []int {
	var blockMap []int

	for i, digit := range fileMap {
		for _ = range digit {
			if i%2 == 0 { // Even
				blockMap = append(blockMap, i/2)
			} else { // Odd
				blockMap = append(blockMap, -1)
			}
		}
	}

	return blockMap
}

func compress1(blockMap []int) []int {
	newBlockMap := make([]int, len(blockMap))
	copy(newBlockMap, blockMap)

	leftIndex := 0
	rightIndex := len(newBlockMap) - 1

	for leftIndex < rightIndex {
		left := &newBlockMap[leftIndex]
		right := &newBlockMap[rightIndex]

		if *left == -1 && *right != -1 {
			*left, *right = *right, *left

			leftIndex++
			rightIndex--

			continue
		}

		if *left != -1 {
			leftIndex++
		}
		if *right == -1 {
			rightIndex--
		}
	}

	return newBlockMap
}

type segment struct {
	index, length int
}

func getSegments(fileMap []int) (files, freeSpaces []segment) {
	var blockIndex int

	for segmentIndex, length := range fileMap {
		if segmentIndex%2 == 0 { // Even
			files = append(files, segment{blockIndex, length})
		} else { // Odd
			freeSpaces = append(freeSpaces, segment{blockIndex, length})
		}

		blockIndex += length
	}

	slices.Reverse(files)

	return
}

func compress2(blockMap, fileMap []int) []int {
	newBlockMap := make([]int, len(blockMap))
	copy(newBlockMap, blockMap)

	files, freeSpaces := getSegments(fileMap)

	for fileIndex, file := range files {
		for freeSpaceIndex, freeSpace := range freeSpaces {
			if freeSpace.index > file.index {
				break
			}

			if freeSpace.length >= file.length {
				// Swap blocks
				idNumber := newBlockMap[file.index]
				for i := 0; i < file.length; i++ {
					newBlockMap[freeSpaces[freeSpaceIndex].index+i] = idNumber
					newBlockMap[files[fileIndex].index+i] = -1
				}

				// Shrink free space
				freeSpaces[freeSpaceIndex].index += file.length
				freeSpaces[freeSpaceIndex].length -= file.length

				break
			}
		}
	}

	return newBlockMap
}

func calculateChecksum(fileMap []int) int {
	var sum int

	for i, num := range fileMap {
		if num == -1 {
			continue
		}

		sum += i * num
	}

	return sum
}

func main() {
	fileMap, err := readInput()
	if err != nil {
		log.Fatalln(err)
	}

	blockMap := convertToBlockMap(fileMap)
	checksum1 := calculateChecksum(compress1(blockMap))
	checksum2 := calculateChecksum(compress2(blockMap, fileMap))

	// Part one
	fmt.Println("Checksum 1:", checksum1)
	// Part two
	fmt.Println("Checksum 2:", checksum2)
}
