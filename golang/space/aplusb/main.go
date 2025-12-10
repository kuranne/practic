package main

import "fmt"

func main() {
	var (
		a int
		b int
	)
	fmt.Scanf("%d %d", &a, &b)
	fmt.Printf("%v\n", a + b)
}