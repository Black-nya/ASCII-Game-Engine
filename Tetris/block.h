#include "../AGE/entity.h"
using namespace GameEngine;
class Block : public Character
{
    int color;
    public: 
    // it's just colored version of character with no content
    Block(int x, int y, int color) : Character{x, y, ' '}, color{color} {}
    void draw(WINDOW *playground) override
    {
        mvwaddch(playground, getY(), getX()*2-1, ' ' | COLOR_PAIR(color) | A_REVERSE);
        mvwaddch(playground, getY(), getX()*2, ' ' | COLOR_PAIR(color) | A_REVERSE);
    }
};