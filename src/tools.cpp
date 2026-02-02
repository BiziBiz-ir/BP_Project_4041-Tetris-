#include "tools.h"
#include <unistd.h>  // for usleep

void clear_screen() {
    std::cout << "\033[2J\033[1;1H" << std::flush;
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

void render(int width, int height, const std::vector<std::vector<int>>& grid) {
    
    clear(); // Clear entire screen

    // Top border
    for (int x = 0; x < width + 2; x++) {
        mvaddch(0, x, ACS_HLINE); // or '_' 
    }

    // Grid content + side borders
    for (int y = 0; y < height; y++) {
        mvaddch(y + 1, 0, ACS_VLINE); // left wall
        for (int x = 0; x < width; x++) {
            char ch = (grid[y][x] ? '#' : ' ');
            mvaddch(y + 1, x + 1, ch);
        }
        mvaddch(y + 1, width + 1, ACS_VLINE); // right wall
    }

    // Bottom border
    for (int x = 0; x < width + 2; x++) {
        mvaddch(height + 1, x, ACS_HLINE);
    }

    // Optional: Add score/info at bottom
    mvprintw(height + 3, 0, "Controls: A/D = move, Q = quit");
    
    refresh(); // Push all changes to screen
}