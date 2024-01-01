#include "../AGE/entity.h"
using namespace GameEngine;
class Cell : public Character
{
    int color;
    bool wall; 
public:
    Cell(int x, int y, char ch ,int color, bool wall) : Character{x, y, ch}, color{color}, wall{wall} {}
    void draw(WINDOW *win)
    {
        if(color >= 0 && color<=6)
            if(wall)
                mvwaddch(win, getY(), getX(), content | COLOR_PAIR(color) | A_REVERSE);
            else
                mvwaddch(win, getY(), getX(), content | COLOR_PAIR(color));
        else
            mvwaddch(win, getY(), getX(), content);
    }
    bool isWall() const { return wall; }
    void setContent(char ch){
        content = ch;
    }
};