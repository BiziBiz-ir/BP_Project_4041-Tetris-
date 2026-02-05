#include "game.h"
#include "tools.h"
#include "block.h"
#include <vector>
#include <limits>
#include <unistd.h> 
#include <ncurses.h>
#include <fstream>
#include <string>

void game(int run) {
    loading_animation();
    clear_screen();

    const int width = 10;
    const int height = 20;

    std::vector<std::vector<int>> grid(height, std::vector<int>(width));
    std::vector<std::vector<int>> def_grid(height, std::vector<int>(width, 0));
    
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);
    nodelay(stdscr, true);
    curs_set(0);

    start_color();
        
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);



    int new_shape = 0;

    Block current_block(width / 2 - 2, 0, random_block()); 
    int next_block = random_block();
    bool is_running = true;
    bool paused = false;

    int game_speed = 500000;

    int score = 0;
    int lines = 0;
    int level = 1;

    const int points [] = {0, 100, 300, 500, 800};
    const int points_for_level[] = {0, 500 , 1000, 3000, 5000};

    
    std::ifstream infile("best.txt"); // load best score
    int best_score = 0;     
    infile >> best_score;  
    infile.close();

    if (run == 1) {
        grid =  def_grid;
    }else {
        load(grid,score,lines,level); //load game
    }

    while (is_running) {
        
        clear();

        // Always render, even when paused
        render(width, height, grid, current_block);

        if (score > best_score) best_score = score;
        
        attron(COLOR_PAIR(5));
        mvprintw(0, width + 5, " _____ _____ _____ ____  ___ ____  \n");
        mvprintw(1, width + 5, "|_   _| ____|_   _|  _ ||_ _/ ___| \n");
        mvprintw(2, width + 5, "  | | |  _|   | | | |_) || ||___ | \n");
        mvprintw(3, width + 5, "  | | | |___  | | |  _ < | | ___) |\n");
        mvprintw(4, width + 5, "  |_| |_____| |_| |_| |_|___|____/ \n");
        attroff(COLOR_PAIR(5));

        attron(COLOR_PAIR(2));
        mvprintw(6, width + 5, "=====================");
        mvprintw(7, width + 5, "||Best: %d", best_score);
        mvprintw(7, width + 24, "||");
        mvprintw(8, width + 5, "||Score: %d", score);
        mvprintw(8, width + 24, "||");
        mvprintw(9, width + 5, "||Lines: %d", lines);
        mvprintw(9, width + 24, "||");
        mvprintw(10, width + 5, "||Level: %d" , level);
        mvprintw(10, width + 24, "||");
        mvprintw(11, width + 5, "||Next block: %c", show_the_block(next_block));
        mvprintw(11, width + 24, "||");
        mvprintw(12, width + 5, "||Press Q to quit");
        mvprintw(12, width + 24, "||");
        mvprintw(13, width + 5, "=====================");
        attroff(COLOR_PAIR(2));
        if (paused) {
            attron(COLOR_PAIR(1));
            mvprintw(15, width + 5, "PAUSED");
            attroff(COLOR_PAIR(1));
        }
        

        // Handle input (always active, even when paused)
        int ch = getch();
        if (ch == 'p' || ch == 'P') {
            paused = !paused; // toggle pause
        } else if (ch == 'q' || ch == 'Q') {
            break; // save game
        }else if (ch == 's' || ch == 'S') {
            save(grid,score,lines,level);
            break;
        }

        // Only move/fall if NOT paused
        if (!paused) {
        // The game speed increases when score is enough
            if (score >= points_for_level[level+1]) {
                level++;
                game_speed-= 100000;
            }   
            // --- Automatic falling ---
            Block test_block = current_block;
            if (!current_block.is_valid_position(grid, width, height)) {
                is_running = false; // Game Over
            }   

            test_block.move_down();
            if (!test_block.is_valid_position(grid, width, height)) {
                current_block.lock(grid);
                score+= 100;

                int cleared = clear_lines(grid, width, height);
                lines += cleared;
                score += points[lines];

                current_block = Block(width / 2 - 2, 0, next_block);
                next_block = random_block();
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
            } else if (ch == 'w' || ch == 'W') {
                current_block.adjust_the_rotation(grid,width,height);
            }else if (ch == ' ' || ch == '\n') {
                while (true) {
                    Block test = current_block;
                    test.move_down();
                    if (test.is_valid_position(grid, width, height)) {
                        current_block.move_down();
                    } else {
                        break; 
                    }
                }
                current_block.lock(grid);
                score+= 100;

                int cleared = clear_lines(grid, width, height);
                lines += cleared;
                score += points[lines];
                
                current_block = Block(width / 2 - 2, 0, next_block); 
                next_block = random_block();

                if (!current_block.is_valid_position(grid, width, height)) {
                    is_running = false; // Game Over
                }
            }
        }

        refresh();
        usleep(game_speed);
    }      


    endwin();

    std::ofstream outfile("best.txt");
    outfile << best_score;


}