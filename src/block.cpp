#include "block.h"
#include <vector>




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
    position_y++;
    
}

bool Block::is_valid_position(const std::vector<std::vector<int>>& grid, int width, int height) const {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (shape[y][x] == 1) {
                int world_x = position_x + x;
                int world_y = position_y + y;

                if (world_x < 0 || world_x >= width) {
                    return false;
                }

                if (world_y >= height) {
                    return false;
                }

                if (world_y >= 0 && grid[world_y][world_x] != 0) {
                    return false;
                }
            }
        }
    }
    return true;
}

void Block::lock(std::vector<std::vector<int>>& grid) const {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (shape[y][x] == 1) {
                int world_x = position_x+ x;
                int world_y = position_y + y;
                if (world_y >= 0 && world_y < (int)grid.size() &&
                    world_x >= 0 && world_x < (int)grid[0].size()) {
                    grid[world_y][world_x] = 1; 
                }
            }
        }
    }
}


Block::Block(int x, int y) : position_x(x), position_y(y) {
const std::vector<std::vector<std::vector<int>>> SHAPES = {
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

    
    shape = SHAPES[0]; 
}

