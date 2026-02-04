#include "menu.h"
#include "tools.h"
#include "game.h"
#include <iostream>
#include <limits>

#ifndef COLOR_DEFINITIONS
#define COLOR_DEFINITIONS
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#endif

void show_help() {
    loading_animation();
    erase_screen();
    std::cout << "=== HELP ===\n";
    std::cout << "Use arrow keys to move\n";
    std::cout << "'w' to rotate\n";
    std::cout << "'Space' to drop instantly\n";
    std::cout << "\nPress any key to return to menu...";
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void run_menu_system() {
    bool exitProgram = false;
    
    while (!exitProgram) {
        erase_screen();
        std::cout << GREEN
        
                  << " _____ _____ _____ ____  ___ ____  \n"
                     "|_   _| ____|_   _|  _ ||_ _/ ___| \n" 
                     "  | | |  _|   | | | |_) || ||___ | \n"
                     "  | | | |___  | | |  _ < | | ___) |\n"
                     "  |_| |_____| |_| |_| |_|___|____/ \n"
                  << RESET << "\n\n";
        
        std::cout << RED 
                  << "1) PLAY THE GAME\n"
                     "2) HELP\n"
                     "3) EXIT\n"
                  << RESET << "\n";

        int input;
        while (true) {
            std::cout << CYAN << "Please enter the number: " << RESET;
            std::cin >> input;
            
            if (std::cin.fail() || input < 1 || input > 3) {
                erase_screen();
                std::cout << RED << "INVALID INPUT\n" << RESET;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else {
                break;
            }
        }

        switch (input) {
            case 1: 
                game();
                break;
            case 2: 
                show_help();
                break;
            case 3: 
                erase_screen();
                std::cout << YELLOW << "Thanks for playing!\n" << RESET;
                exitProgram = true;
                break;
        }
    }
}

int main () {
    run_menu_system();
    return 0;
}