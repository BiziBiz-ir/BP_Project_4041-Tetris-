#include "game.h"
#include "tools.h"
#include "block.h"
#include <vector>
#include <limits>
#include <unistd.h> 
#include <ncurses.h>

void game() {
    loading_animation();
    clear_screen();

    const int width = 10;
    const int height = 20;
    std::vector<std::vector<int>> grid(height, std::vector<int>(width, 0));

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);
    nodelay(stdscr, true);
    curs_set(0);

    Block current_block(width / 2 - 2, 0); 
    bool is_running = true;
    bool paused = false;

while (is_running) {
    clear();

    // Always render, even when paused
    render(width, height, grid, current_block);

    // Handle input (always active, even when paused)
    int ch = getch();
    if (ch == 'p' || ch == 'P') {
        paused = !paused; // toggle pause
    } else if (ch == 'q' || ch == 'Q') {
        break;
    }

    // Only move/fall if NOT paused
    if (!paused) {
        // --- Automatic falling ---
        Block test_block = current_block;
        test_block.move_down();
        if (!test_block.is_valid_position(grid, width, height)) {
            current_block.lock(grid);
            current_block = Block(width / 2 - 2, 0);
            if (!current_block.is_valid_position(grid, width, height)) {
                is_running = false;
            }
        } else {
            current_block.move_down();
        }

        // --- Player movement (A/D/S) ---
        if (ch == 'a' || ch == 'A' || ch == KEY_LEFT) {
            Block test = current_block;
            test.move_left();
            if (test.is_valid_position(grid, width, height)) {
                current_block.move_left();
            }
        } else if (ch == 'd' || ch == 'D' || ch == KEY_RIGHT) {
            Block test = current_block;
            test.move_right();
            if (test.is_valid_position(grid, width, height)) {
                current_block.move_right();
            }
        } else if (ch == 's' || ch == 'S' || ch == KEY_DOWN) {
            Block test = current_block;
            test.move_down();
            if (test.is_valid_position(grid, width, height)) {
                current_block.move_down();
            }
        }
    } else {
        // Optional: show "PAUSED" message
        mvprintw(height + 3, 0, "PAUSED - Press P to resume");
    }

    refresh();
    usleep(300000);
}

    endwin();
}