#include "../AGE/player.h"
using namespace GameEngine;
class Tetromino;
class Tetris;
class ControlledBlock : public Player{
    bool collision(Tetromino* t, Tetris* g, int dx, int dy);
public:
    ControlledBlock(Tetromino* block);
    void update(int input);
};