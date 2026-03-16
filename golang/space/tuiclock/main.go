package main

import (
	"fmt"
	"time"

	tea "github.com/charmbracelet/bubbletea"
	"github.com/charmbracelet/lipgloss"
)

var style = lipgloss.NewStyle().
	Bold(true).
	Foreground(lipgloss.Color("#FAFAFA")).
	Background(lipgloss.Color("#7D56F4")).
	Padding(1, 3).
	Margin(1)

type model struct {
	t time.Time
}

type tickMsg time.Time

func tick() tea.Cmd {
	return tea.Tick(time.Second, func(t time.Time) tea.Msg {
		return tickMsg(t)
	})
}

func (m model) Init() tea.Cmd {
	return tick()
}

func (m model) Update(msg tea.Msg) (tea.Model, tea.Cmd) {
	switch msg := msg.(type) {
	case tea.KeyMsg:
		if msg.String() == "q" || msg.String() == "ctrl+c" {
			return m, tea.Quit
		}
	case tickMsg:
		m.t = time.Time(msg)
		return m, tick()
	}
	return m, nil
}

func (m model) View() string {
	s := m.t.Format("15:04:05")
	return "\n" + style.Render("TIME: "+s) + "\n\n (press q to quit)"
}

func main() {
	p := tea.NewProgram(model{t: time.Now()})
	if _, err := p.Run(); err != nil {
		fmt.Printf("Error: %v", err)
	}
}
