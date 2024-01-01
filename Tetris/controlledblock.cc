#include "controlledblock.h"
#include "tetromino.h"
#include "tetris.h"
#include <vector>
#include "block.h"
#include "../AGE/game.h"
#include "../AGE/entity.h"
#include "../AGE/player.h"
#include "../AGE/movement.h"
ControlledBlock::ControlledBlock(Tetromino *t) : Player{t} {}
bool ControlledBlock::collision(Tetromino *t, Tetris *g, int dy, int dx)
{

    for (auto &p : t->allPoints())
    {
        auto [x, y, z] = p;
        if (g->grid[y + dy][x + dx])
        {
            return true;
        }
    }
    return false;
}
void ControlledBlock::update(int input)
{
    // check if the tetromino exists
    if (entity)
    {
        Tetromino *t = dynamic_cast<Tetromino *>(entity);
        Tetris *g = dynamic_cast<Tetris *>(t->getGame());
        auto &[minx, maxx, miny, maxy] = t->bound;

        Move *temp = nullptr;
        switch (input)
        {
        case 'a':
            if (minx > 1 && !collision(t, g, 0, -1))
                // move left by 1
                temp = new Move{-1, 0};
            break;
        case 's':
            // faster move down
            t->cur = t->tick;
            break;
        case 'd':
            // move right by 1
            if (maxx < g->getWidth() && !collision(t, g, 0, 1))
                temp = new Move{1, 0};
            break;
        case 'w':
            // rotate clockwise
            t->rotate();
            break;
        default:
            break;
        }
        if (temp)
        {
            temp->transform(*t);
            delete temp;
        }
        if(t->cur == t->tick){
            if (maxy == g->getHeight() || collision(t, g, 1, 0))
            {
                t->release(); // breaks it into blocks
                setPlayer(g->generate()); // get a new tetromino
                goto label;
            }
            else if (!collision(t, g, 1, 0))
            {
                t->update();
                t->cur = 0;
            }
        }
        t->cur++;
        label:;
        std::vector<int> deleted_rows;
        for (int row = g->getHeight(); row >0; row--)
        {
            for (int col = 1; col <= g->getWidth(); col++)
            {
                if (!g->grid[row][col])
                {
                    goto LOOP;
                }
            }
            deleted_rows.push_back(row);
            for (int col = 1; col <= g->getWidth(); col++)
            {
                g->destroyEntity(g->grid[row][col]);
                g->grid[row][col] = nullptr;
            }  
        LOOP:;
        }
        deleted_rows.push_back(0);
        if(deleted_rows.size()>1){
            for(int i=0; i<deleted_rows.size()-1; i++){

                int low = deleted_rows[i];
                int hi = deleted_rows[i+1];
                // move down all rows from (low,hi) by i+1
                for(int r = low-1; r>hi; r--){
                    for(int col = 1; col <=g->getWidth(); col++){
                        if(g->grid[r][col]){
                            Block* tmp = g->grid[r][col];
                            g->grid[r][col] = nullptr;
                            tmp->setY(tmp->getY()+i+1);
                            g->grid[r+i+1][col] = tmp;
                        }
                    }
                }
            }
        }
    }
}
