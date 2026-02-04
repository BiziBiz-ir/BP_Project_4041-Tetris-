#include "tools.h"
#include "block.h"
#include <unistd.h>  // for usleep
#include <cstdlib>  // for system()
#include <algorithm>
#include <ncurses.h>
#include <vector>
#include <random>
#include <iostream>

void init_colorss() {
    
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);
}

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

void render(int width, int height,
            const std::vector<std::vector<int>>& grid,
            const Block& current_block) {
    //start_color();
    init_colorss();
    // Draw top border
    attron(COLOR_PAIR(1));
    mvaddch(0, 0, '+');
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(6));
    for (int i = 0; i < width; i++) mvaddch(0, i + 1, '-');
    attroff(COLOR_PAIR(6));
    
    attron(COLOR_PAIR(1));
    mvaddch(0, width + 1, '+');
    attroff(COLOR_PAIR(1));

    // Draw rows
    for (int y = 0; y < height; y++) {
        attron(COLOR_PAIR(6));
        mvaddch(y + 1, 0, '|'); // left wall
        attroff(COLOR_PAIR(6));

        attron(COLOR_PAIR(4));


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
        }attroff(COLOR_PAIR(4));


        attron(COLOR_PAIR(6));
        mvaddch(y + 1, width + 1, '|'); // right wall
        attroff(COLOR_PAIR(6));
    }

    // Bottom border
    attron(COLOR_PAIR(1));
    mvaddch(height + 1, 0, '+');
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(6));
    for (int i = 0; i < width; i++) mvaddch(height + 1, i + 1, '-');
    attron(COLOR_PAIR(6));

    attron(COLOR_PAIR(1));
    mvaddch(height + 1, width + 1, '+');
    attron(COLOR_PAIR(1));
}

int clear_lines(std::vector<std::vector<int>>& grid, int width, int height) {
    std::vector<std::vector<int>> new_grid;
    int lines_cleared = 0;

    
    for (int y = height - 1; y >= 0; y--) {
        bool is_full = true;
        for (int x = 0; x < width; x++) {
            if (grid[y][x] == 0) {
                is_full = false;
                break;
            }
        }

        if (is_full) {
            lines_cleared++;
        } else {
            new_grid.push_back(grid[y]); 
        }
    }

    std::reverse(new_grid.begin(), new_grid.end());


    while ((int)new_grid.size() < height) {
        new_grid.insert(new_grid.begin(), std::vector<int>(width, 0));
    }

    grid = new_grid;
    return lines_cleared;
}


int random_block() {

    std::random_device rd;

    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0, 6);
    
    return distribution(generator);
}
char show_the_block(int shape) {
    switch (shape)
    {
    case 0:
        return 'I';
        break;
    case 1:
        return '0';
        break;
    case 2: 
        return  'T';
    case 3:
        return 'S';
        break;
    case 4: 
        return 'Z';
        break;
    case 5:
        return 'J';
        break;
    case 6: 
        return 'L';
        break;
    default:
        break;
    }
    return 'N';
}

