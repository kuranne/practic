package main

import "fmt"

func main() {
	var m, n, i, j, temp int
	numbers := make([]int, m*n*2)
	fmt.Scanf("%d%d", &m, &n)
	for i = 0; i < m*2; i++ {
		for j = 0; j < n; j++ {
			fmt.Scan(&temp)
			numbers[(i*3)+j] = temp
		}
	}
	for i = 0; i < m; i++ {
		for j = 0; j < n; j++ {
			fmt.Printf("%v ", numbers[(i*3)+j]+numbers[((i+3)*3)+j])
		}
		fmt.Println("")
	}
}
