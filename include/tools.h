#ifndef TOOLS_H
#define TOOLS_H

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include "block.h"

// ANSI Color Codes (NO using namespace std here!)
#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

// Utility functions
void clear_screen();
void erase_screen();
void loading_animation();
void render(int width, int height,
            const std::vector<std::vector<int>>& grid,
            const Block& current_block);

#endif // TOOLS_H