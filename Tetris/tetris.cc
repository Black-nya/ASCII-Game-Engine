#include "tetris.h"
#include "util.h"
#include <curses.h>
#include "tetromino.h"
#include "controlledblock.h"
Tetris::Tetris() : Game{BorderType::Solid}
{
    player = new ControlledBlock(generate());
}
Tetromino *Tetris::generate()
{
    int color = getRandom(0, 6);
    Tetromino *temp = nullptr;
    switch (getRandom(0,6))
    {
    case 0:
        temp = new I{this, color};
        break;
    case 1:
        temp = new O{this, color};
        break;
    case 2:
        temp = new T{this, color};
        break;
    case 3:
        temp = new L{this, color};
        break;
    case 4:
        temp = new J{this, color};
        break;
    case 5:
        temp = new S{this, color};
        break;
    case 6:
        temp = new Z{this, color};
        break;
    default:
        throw "Impossible!";
    }
    
    
    for(auto & p: temp->allPoints()){
        auto&[x,y,z] = p;
        if(grid[y][x]){
            end = true;
        }
    }
    
    return temp;
} // generate a terminos