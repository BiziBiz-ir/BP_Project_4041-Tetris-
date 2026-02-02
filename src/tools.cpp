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

void render(int width, int height, const std::vector<std::vector<int>>& grid) {
    // Top border
    for (int i = 0; i < width + 2; ++i) {
        std::cout << WHITE << "_";
    }
    std::cout << RESET << "\n";

    // Grid content
    for (int i = 0; i < height; ++i) {
        std::cout << "|";
        for (int j = 0; j < width; ++j) {
            if (grid[i][j] == 0) {
                std::cout << ".";
            } else if (grid[i][j] == 1) {
                std::cout << "#";
            }
        }
        std::cout << "|\n";
    }

    // Bottom border
    for (int i = 0; i < width + 2; ++i) {
        std::cout << WHITE << "-";
    }
    std::cout << RESET << "\n";
}