#include "block.h"
#include <vector>
#include <algorithm>

void Block::rotate() {
    // Step 1: Transpose the 4x4 matrix
    std::vector<std::vector<int>> new_shape(4, std::vector<int>(4, 0));
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            new_shape[j][i] = shape[i][j];
        }
    }

    // Step 2: Reverse each row → clockwise rotation
    for (int i = 0; i < 4; i++) {
        std::reverse(new_shape[i].begin(), new_shape[i].end());
    }

    shape = new_shape;
}

bool Block::adjust_the_rotation(std::vector<std::vector<int>>& grid, int width, int height) {
    // Save original state
    std::vector<std::vector<int>> original_shape = shape;
    int original_x = position_x;
    int original_y = position_y;

    // Try to rotate
    rotate();

    // If valid immediately, done!
    if (is_valid_position(grid, width, height)) {
        return true;
    }

    // Otherwise, try small adjustments
    std::vector<std::pair<int, int>> offsets = {
        { -1, 0 },  // left
        { 1, 0 },   // right
        { -2, 0 },  // further left
        { 2, 0 },   // further right
        { 0, -1 }   // up (sometimes needed)
    };

    for (const auto& offset : offsets) {
        position_x = original_x + offset.first;
        position_y = original_y + offset.second;
        if (is_valid_position(grid, width, height)) {
            return true; // success with adjustment
        }
    }

    // If all fail, revert
    shape = original_shape;
    position_x = original_x;
    position_y = original_y;
    return false;
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

