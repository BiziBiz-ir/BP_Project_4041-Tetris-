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
    nodelay(stdscr, true);  // ← this enables real-time input (no Enter)
    curs_set(0);

    Block current_block(width / 2 - 2, 0); // center it (adjust for 4-cell width)
    bool is_running = true;

    while (is_running) {
        // Clear screen (ncurses style)
        clear();

        // Render grid + active block (you'll update render() next)
        render(width, height, grid, current_block);

        // Get key (non-blocking)
        int ch = getch();

        // Save original position
        int old_x = current_block.position_x;
        int old_y = current_block.position_y;

        // Handle input
        if (ch == 'a' || ch == 'A' || ch == KEY_LEFT) {
            current_block.move_left();
        } else if (ch == 'd' || ch == 'D' || ch == KEY_RIGHT) {
            current_block.move_right();
        } else if (ch == 's' || ch == 'S' || ch == KEY_DOWN) {
            current_block.move_down();
        } else if (ch == 'q' || ch == 'Q') {
            break; // quit
        }
        // Ignore all other keys (including garbage input)

        // Check if new position is inside bounds (0 <= x <= width - 1)
        // Note: we only check X here because Y < 0 is okay (block entering from top)
        bool valid_x = true;
        for (int y = 0; y < 4; y++) {
            for (int x = 0; x < 4; x++) {
                if (current_block.shape[y][x] == 1) {
                    int world_x = current_block.position_x   + x;
                    if (world_x < 0 || world_x >= width) {
                        valid_x = false;
                        break;
                    }
                }
            }
            if (!valid_x) break;
        }

        // If move caused out-of-bounds, revert
        if (!valid_x) {
            current_block.position_x = old_x;
            current_block.position_y = old_y;
        }

        // Optional: small delay to control speed
        usleep(100000); // 100ms → ~10 FPS
    }

    endwin();
}
