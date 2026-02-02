#include "menu.h"
#include "tools.h"
#include "game.h"
#include <iostream>
#include <limits>

void help() {
    loading_animation();
    clear_screen();
    std::cout << "=== HELP ===\n";
    std::cout << "Use arrow keys to move\n";
    std::cout << "'z' to rotate left, 'x' to rotate right\n";
    std::cout << "'Space' to drop instantly\n";
    std::cout << "\nPress any key to return to menu...";
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    menu();
}

void menu() {
    clear_screen();
    std::cout << GREEN 
              << " _____ _____ _____ ____  ___ ____  \n"
                 "|_   _| ____|_   _|  _ \\|_ _|  _ \\ \n"
                 "  | | |  _|   | | | |_) || || | | |\n"
                 "  | | | |___  | | |  _ < | || |_| |\n"
                 "  |_| |_____| |_| |_| \\_|___|____/ \n"
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
            clear_screen();
            std::cout << RED << "INVALID INPUT\n" << RESET;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            break;
        }
    }

    switch (input) {
        case 1: game(); break;
        case 2: help(); break;
        case 3: 
            clear_screen();
            std::cout << YELLOW << "Thanks for playing!\n" << RESET;
            exit(0);
    }
}