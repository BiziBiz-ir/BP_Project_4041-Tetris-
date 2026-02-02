#include "block.h"

void Block::rotate() {
    rotation = (rotation + 90) % 360;  
}

void Block::move_left(){
    if (position_x > 0 && position_x < 10) {
        position_x++;
    }
}

void Block::move_right (){
    if (position_x > 0 && position_x < 10) {
        position_x++;
    }
}

Block::Block(int x, int y) 
    : position_x(x), position_y(y), rotation(0), shape("") {}