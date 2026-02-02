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
    bool is_running = true;

    Block corrent_block(5,20);

    initscr();
    cbreak();
    noecho();
    keypad(stdscr,true);
    nodelay(stdscr,true);

    while (is_running) {
        clear_screen();
        render(width, height, grid); 

        int ch = getch(); 
        if (ch == 'a' || ch == KEY_LEFT) {
            corrent_block.move_left();
        } else if (ch == 'd' || ch == KEY_RIGHT) {
            corrent_block.move_right();
        } else if (ch == 'q') {
            break;
        }
    
        while (getchar() != '\n');
    }
}

