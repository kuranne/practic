package main

import (
	"fmt"
	"strings"
	"time"

	tea "github.com/charmbracelet/bubbletea"
)

var digits = map[rune][]string{
	'0': {"███", "█ █", "█ █", "█ █", "███"},
	'1': {"  █", "  █", "  █", "  █", "  █"},
	'2': {"███", "  █", "███", "█  ", "███"},
	'3': {"███", "  █", "███", "  █", "███"},
	'4': {"█ █", "█ █", "███", "  █", "  █"},
	'5': {"███", "█  ", "███", "  █", "███"},
	'6': {"███", "█  ", "███", "█ █", "███"},
	'7': {"███", "  █", "  █", "  █", "  █"},
	'8': {"███", "█ █", "███", "█ █", "███"},
	'9': {"███", "█ █", "███", "  █", "███"},
	':': {"   ", " █ ", "   ", " █ ", "   "},
}

type model struct{ t time.Time }
type tickMsg time.Time

func (m model) Init() tea.Cmd {
	return tea.Tick(time.Second, func(t time.Time) tea.Msg { return tickMsg(t) })
}

func (m model) Update(msg tea.Msg) (tea.Model, tea.Cmd) {
	if k, ok := msg.(tea.KeyMsg); ok && k.String() == "q" {
		return m, tea.Quit
	}
	if t, ok := msg.(tickMsg); ok {
		m.t = time.Time(t)
		return m, m.Init()
	}
	return m, nil
}

func (m model) View() string {
	strTime := m.t.Format("15:04:05")
	output := make([]string, 5)

	for _, char := range strTime {
		for i := 0; i < 5; i++ {
			output[i] += digits[char][i] + "  "
		}
	}

	return "\n" + strings.Join(output, "\n") + "\n\n (press q to quit)"
}

func main() {
	if _, err := tea.NewProgram(model{t: time.Now()}).Run(); err != nil {
		fmt.Println(err)
	}
}
