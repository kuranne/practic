package main

import (
	"fmt"
)

func main() {
	var (
		n int
		i int
	)
	ptoc := 3
	fmt.Scanf("%d", &n)
	prime := make([]int, n)
	prime[0] = 2
	if n < 1 {
		fmt.Println("Prime at n must be more than zero")
	} else if n > 1 {
		for i < n {
			isPrime := true
			for j := 0; j < n; j++ {
				if prime[j] != 0 {
					if ptoc%prime[j] == 0 {
						isPrime = false
						break
					}
				}
			}
			if isPrime {
				prime[i] = ptoc
				i++
			}
			ptoc += 2
		}
	}
	fmt.Printf("%v\n", prime[n-2])
}
