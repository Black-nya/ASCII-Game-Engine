#ifndef _TETRIS_
#define _TETRIS_
#include "../AGE/game.h"
using namespace GameEngine;
class Tetromino;
class Block;
class Tetris : public Game
{
public:
    int height = 20;
    int width = 10;
    Block* grid[21][11] = {};
    Tetris();
    Tetromino* generate();
    const int getWidth() const {return width;}
    const int getHeight() const {return height;}
};
#endif