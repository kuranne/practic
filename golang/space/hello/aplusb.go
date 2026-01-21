package main

import "fmt"

func main() {
	var (
		a int32
		b int32
	)
	fmt.Scanf("%d %d", &a, &b)
	fmt.Println("%v", a+b)
}
