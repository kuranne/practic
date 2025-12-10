import curses
import random
import time
from enum import Enum
from typing import List, Tuple


class Direction(Enum):
    UP = (-1, 0)
    DOWN = (1, 0)
    LEFT = (0, -1)
    RIGHT = (0, 1)


class SnakeGame:
    def __init__(self, stdscr):
        self.stdscr = stdscr
        self.height, self.width = stdscr.getmaxyx()

        # Game boundaries (leave space for borders and UI)
        self.game_height = self.height - 4
        self.game_width = self.width - 4

        # Initialize game state
        self.reset_game()

        # Setup curses
        curses.curs_set(0)  # Hide cursor
        stdscr.nodelay(1)  # Non-blocking input
        stdscr.timeout(100)  # Game speed (milliseconds)

        # Initialize colors
        curses.start_color()
        curses.init_pair(1, curses.COLOR_GREEN, curses.COLOR_BLACK)  # Snake
        curses.init_pair(2, curses.COLOR_RED, curses.COLOR_BLACK)  # Food
        curses.init_pair(3, curses.COLOR_YELLOW, curses.COLOR_BLACK)  # Score
        curses.init_pair(4, curses.COLOR_WHITE, curses.COLOR_RED)  # Game Over

    def reset_game(self):
        """Reset game to initial state"""
        # Snake starts in the middle
        start_y = self.game_height // 2
        start_x = self.game_width // 2
        self.snake = [
            (start_y, start_x),
            (start_y, start_x - 1),
            (start_y, start_x - 2),
        ]
        self.direction = Direction.RIGHT
        self.score = 0
        self.food = self.generate_food()
        self.game_over = False

    def generate_food(self) -> Tuple[int, int]:
        """Generate food at random position not occupied by snake"""
        while True:
            food_y = random.randint(1, self.game_height - 2)
            food_x = random.randint(1, self.game_width - 2)
            if (food_y, food_x) not in self.snake:
                return (food_y, food_x)

    def draw_border(self):
        """Draw game border"""
        # Top and bottom borders
        for x in range(self.game_width):
            self.stdscr.addch(0, x, "─")
            self.stdscr.addch(self.game_height - 1, x, "─")

        # Left and right borders
        for y in range(self.game_height):
            self.stdscr.addch(y, 0, "│")
            self.stdscr.addch(y, self.game_width - 1, "│")

        # Corners
        self.stdscr.addch(0, 0, "┌")
        self.stdscr.addch(0, self.game_width - 1, "┐")
        self.stdscr.addch(self.game_height - 1, 0, "└")
        self.stdscr.addch(self.game_height - 1, self.game_width - 1, "┘")

    def draw_snake(self):
        """Draw the snake on screen"""
        for i, (y, x) in enumerate(self.snake):
            if i == 0:  # Head
                self.stdscr.addch(y, x, "●", curses.color_pair(1) | curses.A_BOLD)
            else:  # Body
                self.stdscr.addch(y, x, "○", curses.color_pair(1))

    def draw_food(self):
        """Draw food on screen"""
        y, x = self.food
        self.stdscr.addch(y, x, "♦", curses.color_pair(2) | curses.A_BOLD)

    def draw_score(self):
        """Draw score and instructions"""
        score_text = f"Score: {self.score}"
        self.stdscr.addstr(self.game_height, 2, score_text, curses.color_pair(3))

        instructions = "Arrow keys: Move | Q: Quit"
        self.stdscr.addstr(self.game_height + 1, 2, instructions)

    def draw_game_over(self):
        """Draw game over screen"""
        game_over_text = "GAME OVER!"
        restart_text = "Press R to restart or Q to quit"

        # Center the text
        y = self.game_height // 2
        x1 = (self.game_width - len(game_over_text)) // 2
        x2 = (self.game_width - len(restart_text)) // 2

        self.stdscr.addstr(y, x1, game_over_text, curses.color_pair(4) | curses.A_BOLD)
        self.stdscr.addstr(y + 2, x2, restart_text)

    def handle_input(self, key):
        """Handle user input"""
        if key == ord("q") or key == ord("Q"):
            return False  # Quit game

        if self.game_over:
            if key == ord("r") or key == ord("R"):
                self.reset_game()
            return True

        # Direction controls
        direction_map = {
            curses.KEY_UP: Direction.UP,
            curses.KEY_DOWN: Direction.DOWN,
            curses.KEY_LEFT: Direction.LEFT,
            curses.KEY_RIGHT: Direction.RIGHT,
        }

        if key in direction_map:
            new_direction = direction_map[key]
            # Prevent moving in opposite direction
            if (
                new_direction.value[0] * -1,
                new_direction.value[1] * -1,
            ) != self.direction.value:
                self.direction = new_direction

        return True

    def update_snake(self):
        """Update snake position"""
        if self.game_over:
            return

        # Calculate new head position
        head_y, head_x = self.snake[0]
        dy, dx = self.direction.value
        new_head = (head_y + dy, head_x + dx)

        # Check wall collision
        if (
            new_head[0] <= 0
            or new_head[0] >= self.game_height - 1
            or new_head[1] <= 0
            or new_head[1] >= self.game_width - 1
        ):
            self.game_over = True
            return

        # Check self collision
        if new_head in self.snake:
            self.game_over = True
            return

        # Add new head
        self.snake.insert(0, new_head)

        # Check food collision
        if new_head == self.food:
            self.score += 10
            self.food = self.generate_food()
        else:
            # Remove tail if no food eaten
            self.snake.pop()

    def run(self):
        """Main game loop"""
        while True:
            # Clear screen
            self.stdscr.clear()

            # Draw game elements
            self.draw_border()

            if not self.game_over:
                self.draw_snake()
                self.draw_food()
            else:
                self.draw_game_over()

            self.draw_score()

            # Refresh screen
            self.stdscr.refresh()

            # Handle input
            key = self.stdscr.getch()
            if not self.handle_input(key):
                break

            # Update game state
            self.update_snake()


def main(stdscr):
    """Main function to run the game"""
    # Check terminal size
    height, width = stdscr.getmaxyx()
    if height < 10 or width < 40:
        stdscr.addstr(0, 0, "Terminal too small! Need at least 40x10 characters.")
        stdscr.addstr(1, 0, "Press any key to exit...")
        stdscr.refresh()
        stdscr.getch()
        return

    # Start the game
    game = SnakeGame(stdscr)
    game.run()


if __name__ == "__main__":
    try:
        curses.wrapper(main)
    except KeyboardInterrupt:
        print("\nGame interrupted by user")
    except Exception as e:
        print(f"An error occurred: {e}")
    finally:
        print("Thanks for playing Snake!")
