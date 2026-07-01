package main

import (
	"fmt"
)

func main() {
	var n, i int
	chk := true
	fmt.Scan(&n)
	number := make([]int, n)

	for i = 0; i < n; i++ {
		fmt.Scan(&number[i])
	}

	for chk {
		for i = 0; i < n; i++ {
			if i != n-1 && number[i] > number[i+1] {
				number[i], number[i+1] = number[i+1], number[i]
				chk = true
				break
			}
			if i == n-1 && number[i] < number[i-1] {
				number[i], number[i-1] = number[i-1], number[i]
				chk = true
				break
			}
			chk = false
		}
	}

	fmt.Printf("%v\n%v\n", number[0], number[n-1])
}
