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

    void rotate();  
    void move_right();
    void move_left();
    void move_down();
    Block(int x, int y);
};

#endif // BLOCK_H

