#include "block.h"
#include <vector>

// In block.cpp or a dedicated shapes file
const std::vector<std::vector<std::vector<int>>> TETROMINO_SHAPES = {
    // I-piece
    {
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    // O-piece
    {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    },
    // T-piece
    {
        {0, 0, 0, 0},
        {0, 1, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0}
    },
    // S-piece
    {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0}
    },
    // Z-piece
    {
        {0, 0, 0, 0},
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    },
    // J-piece
    {
        {0, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0}
    },
    // L-piece
    {
        {0, 0, 0, 0},
        {0, 0, 1, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0}
    }
};

void Block::rotate() {
    rotation = (rotation + 90) % 360;  
}

void Block::move_left(){
    position_x--;
}

void Block::move_right (){
    position_x++;

}


void Block::move_down(){
    position_x++;
    
}

Block::Block(int x, int y) : position_x(x), position_y(y) {
    // You MUST assign a shape here!
    // For testing, pick the first shape:
    static const std::vector<std::vector<std::vector<int>>> SHAPES = {
        {{0,0,0,0}, {1,1,1,1}, {0,0,0,0}, {0,0,0,0}}, // I
        {{0,0,0,0}, {0,1,1,0}, {0,1,1,0}, {0,0,0,0}}  // O
        // ... add all 7 if you want
    };

    // Just pick one for now (e.g., index 0)
    shape = SHAPES[0]; // ← critical: don't leave shape_ empty!
}