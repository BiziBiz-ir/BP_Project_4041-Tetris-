#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <vector>

class Block {
public:
    int position_x;
    int position_y;
    int rotation;

    std::vector<std::vector<int>> shape;

    bool is_valid_position(const std::vector<std::vector<int>>& grid, int width, int height) const;

    void lock(std::vector<std::vector<int>>& grid) const;

    void rotate();  
    void move_right();
    void move_left();
    void move_down();
    Block(int x, int y);

    bool adjust_the_rotation(std::vector<std::vector<int>>& grid, int width, int height);
};

#endif // BLOCK_H

