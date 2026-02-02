#ifndef BLOCK_H
#define BLOCK_H

#include <string>

class Block {
public:
    int position_x;
    int position_y;
    int rotation;
    std::string shape;

    void rotate();  
    void move_right();
    void move_left();
    Block(int x, int y);
};

#endif // BLOCK_H