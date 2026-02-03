#include "tools.h"
#include "block.h"
#include <unistd.h>  // for usleep
#include <cstdlib>  // for system()

void clear_screen() {
    std::cout << "\033[2J\033[1;1H" << std::flush;  
}
void erase_screen() {
    system("clear");
}

void loading_animation() {
    const int barWidth = 50;
    for (int i = 0; i <= 100; i++) {
        int pos = barWidth * i / 100;
        std::cout << "\r[";
        for (int j = 0; j < barWidth; ++j) {
            if (j < pos)
                std::cout << GREEN << "█" << RESET;
            else
                std::cout << "░";
        }
        std::cout << "] " << i << "%" << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    std::cout << std::endl;
}

#include <ncurses.h>
#include <vector>

void render(int width, int height,
            const std::vector<std::vector<int>>& grid,
            const Block& current_block) {
    // Draw top border
    mvaddch(0, 0, '+');
    for (int i = 0; i < width; i++) mvaddch(0, i + 1, '-');
    mvaddch(0, width + 1, '+');

    // Draw rows
    for (int y = 0; y < height; y++) {
        mvaddch(y + 1, 0, '|'); // left wall

        for (int x = 0; x < width; x++) {
            char ch = ' ';

            // Check if active block occupies (x,y)
            int local_x = x - current_block.position_x;
            int local_y = y - current_block.position_y;
            if (local_x >= 0 && local_x < 4 &&
                local_y >= 0 && local_y < 4 &&
                current_block.shape[local_y][local_x] == 1) {
                ch = 'X';
            }
            // Else, check settled blocks
            else if (grid[y][x] != 0) {
                ch = 'X';
            }

            mvaddch(y + 1, x + 1, ch);
        }

        mvaddch(y + 1, width + 1, '|'); // right wall
    }

    // Bottom border
    mvaddch(height + 1, 0, '+');
    for (int i = 0; i < width; i++) mvaddch(height + 1, i + 1, '-');
    mvaddch(height + 1, width + 1, '+');
}