#include "game.h"
#include "tools.h"
#include "block.h"
#include <vector>
#include <limits>
#include <unistd.h>  // for getchar()

void game() {
    loading_animation();
    clear_screen();

    const int width = 10;
    const int height = 20;  // Fixed typo: "higth" → "height"

    std::vector<std::vector<int>> grid(height, std::vector<int>(width, 0));
    bool is_running = true;

    while (is_running) {
        clear_screen();
        render(width, height, grid);  // Fixed parameter name

        // Simple blocking input (for demo - ncurses would be better for real game)
        std::cout << "Press 'q' to quit, 'd' to move right: ";
        int ch = getchar();
        if (ch == 'q' || ch == 'Q') {
            is_running = false;
        } else if (ch == 'd' || ch == 'D') {
            // TODO: Implement block movement logic
        }
        // Consume newline
        while (getchar() != '\n');
    }
}

