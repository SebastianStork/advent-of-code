package main

import (
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
	"unicode"
)

type equation struct {
	result  int
	numbers []int
}

func isNotNumber(c rune) bool {
	return !unicode.IsNumber(c)
}

func readInput() (equations []equation, err error) {
	content, err := os.ReadFile("input")
	if err != nil {
		return
	}

	lines := strings.Split(strings.TrimSpace(string(content)), "\n")
	for _, line := range lines {
		parts := strings.FieldsFunc(line, isNotNumber)
		nums := make([]int, len(parts))

		for i, part := range parts {
			nums[i], _ = strconv.Atoi(part)
		}

		equations = append(equations, equation{result: nums[0], numbers: nums[1:]})
	}

	return
}

func pow(base, exp int) int {
	result := 1
	for {
		if exp&1 == 1 {
			result *= base
		}
		exp >>= 1
		if exp == 0 {
			break
		}
		base *= base
	}
	return result
}

func equationResult(nums []int, operatorMask, operatorSpace int) int {
	result := nums[0]

	for operatorIndex := 0; operatorIndex < len(nums)-1; operatorIndex++ {
		currentOperator := (operatorMask / pow(operatorSpace, operatorIndex)) % operatorSpace
		currentNum := nums[operatorIndex+1]

		switch currentOperator {
		case 0:
			result += currentNum
		case 1:
			result *= currentNum
		case 2:
			result, _ = strconv.Atoi(fmt.Sprintf("%d%d", result, currentNum))
		default:
			panic("Unsupported operator")
		}
	}

	return result
}

func isValidEquation(eq equation, operatorSpace int) bool {
	maxOperatorMask := pow(operatorSpace, len(eq.numbers)-1) - 1

	for operatorMask := 0; operatorMask <= maxOperatorMask; operatorMask++ {
		if equationResult(eq.numbers, operatorMask, operatorSpace) == eq.result {
			return true
		}
	}

	return false
}

func totalResult(equations []equation) (result, resultWithConcat int) {
	for _, eq := range equations {
		if isValidEquation(eq, 2) {
			result += eq.result
			resultWithConcat += eq.result
		} else if isValidEquation(eq, 3) {
			resultWithConcat += eq.result
		}
	}

	return
}

func main() {
	equations, err := readInput()
	if err != nil {
		log.Fatalln(err)
	}

	result, resultWithConcat := totalResult(equations)

	// Part one
	fmt.Println("Total calibration result:", result)
	// Part two
	fmt.Println("Total calibration result with concatenation:", resultWithConcat)
}
