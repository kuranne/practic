package main

import (
	"bufio"
	"fmt"
	"os"
	"os/exec"
	"time"
)

var digits = [10][5]string{
	{"███", "█ █", "█ █", "█ █", "███"}, //0
	{"  █", "  █", "  █", "  █", "  █"}, //1
	{"███", "  █", "███", "█  ", "███"}, //2
	{"███", "  █", "███", "  █", "███"}, //3
	{"█ █", "█ █", "███", "  █", "  █"}, //4
	{"███", "█  ", "███", "  █", "███"}, //5
	{"███", "█  ", "███", "█ █", "███"}, //6
	{"███", "  █", "  █", "  █", "  █"}, //7
	{"███", "█ █", "███", "█ █", "███"}, //8
	{"███", "█ █", "███", "  █", "███"}, //9
}

func clearScreen() {
	cmd := exec.Command("clear")
	cmd.Stdout = os.Stdout
	cmd.Run()
}

func drawTime(hour, min, sec int) {
	h1, h2 := hour/10, hour%10
	m1, m2 := min/10, min%10
	s1, s2 := sec/10, sec%10

	for row := 0; row < 5; row++ {
		fmt.Printf("%s %s   %s %s   %s %s\n",
			digits[h1][row], digits[h2][row],
			digits[m1][row], digits[m2][row],
			digits[s1][row], digits[s2][row])
	}
}

func main() {
	reader := bufio.NewReader(os.Stdin)
	countdown := 0

	for {
		clearScreen()

		// Problem here
		if reader.Buffered() > 0 {
			input, _ := reader.ReadByte()
			if input == 'q' || input == 'Q' {
				break
			}
			if input >= '0' && input <= '9' {
				countdown = int(input-'0') * 60
			}
		}

		if countdown > 0 {
			hours := countdown / 3600
			minutes := (countdown % 3600) / 60
			seconds := countdown % 60
			drawTime(hours, minutes, seconds)
			countdown--
		} else {
			now := time.Now()
			drawTime(now.Hour(), now.Minute(), now.Second())
		}

		fmt.Println("\nPress 'q' to quit, 0-9 to start countdown (minutes).")
		time.Sleep(1 * time.Second)
	}
}
