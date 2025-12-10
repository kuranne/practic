package main

import (
	"fmt"
)

func main() {
	var (
		n, i, j, ques int
		count         int = 0
		isEqual       bool
	)

	fmt.Scan(&n)
	temp := make([]int, n)
	for i = 0; i < n; i++ {
		fmt.Scan(&ques)
		temp[i] = ques % 42
		isEqual = false
		if i != 0 {
			for j = 0; j < i; j++ {
				if temp[j] == temp[i] {
					isEqual = true
					break
				}
			}
		}
		if isEqual {
			continue
		}
		count++
	}
	fmt.Printf("%v\n", count)
}
