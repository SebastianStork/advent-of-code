package main

import (
	"fmt"
	"testing"
)

var rules = map[int][]int{
	29: {13},
	47: {53, 13, 61, 29},
	53: {29, 13},
	61: {13, 53, 29},
	75: {29, 53, 47, 61, 13},
	97: {13, 61, 47, 29, 53, 75},
}

var updates = [][]int{
	{75, 47, 61, 53, 29},
	{97, 61, 53, 29, 13},
	{75, 29, 13},
	{75, 97, 47, 61, 53},
	{61, 13, 29},
	{97, 13, 75, 29, 47},
}

func TestIsCorrectlyOrdered(t *testing.T) {
	tests := []struct {
		input []int
		want  bool
	}{
		{updates[0], true},
		{updates[1], true},
		{updates[2], true},
		{updates[3], false},
		{updates[4], false},
		{updates[5], false},
	}

	for _, test := range tests {
		testName := fmt.Sprint(test.input)
		t.Run(testName, func(t *testing.T) {
			got := isCorrectlyOrdered(rules, test.input)

			if got != test.want {
				t.Errorf("got %t, want %t", got, test.want)
			}
		})
	}
}

func TestSumOfMiddlePages(t *testing.T) {
	correctSum, correctedSum := calculateMiddlePageSums(rules, updates)

	t.Run("correctSum", func(t *testing.T) {
		want := 143
		got := correctSum

		if got != want {
			t.Errorf("got %d, want %d", got, want)
		}
	})

	t.Run("correctedSum", func(t *testing.T) {
		want := 123
		got := correctedSum

		if got != want {
			t.Errorf("got %d, want %d", got, want)
		}
	})
}
