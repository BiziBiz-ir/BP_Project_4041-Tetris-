#include "block.h"

void Block::rotate() {
    rotation = (rotation + 90) % 360;  // Cleaner rotation logic
}

Block::Block(int x, int y) 
    : position_x(x), position_y(y), rotation(0), shape("") {}