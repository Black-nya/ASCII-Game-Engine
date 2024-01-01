#include "chara.h"
#include "cell.h"
#include "../AGE/movement.h"
#include "pacman.h"
using GameEngine::Player;
using GameEngine::Movement;
Chara::Chara(int x, int y) : Player{new Cell{x, y, '<', 2, false}}, direction{0}
{
}
void Chara::update(int input)
{   
    if (Cell *b = dynamic_cast<Cell *>(entity))
    {
        switch (input)
        {
        case 'w':
            direction = 3;
            break;
        case 'a':
            direction = 0;
            break;
        case 's':
            direction = 1;
            break;
        case 'd':
            direction = 2;
            break;
        default:
            break;
        }
        Movement* temp = nullptr;
        PacMan* g = dynamic_cast<PacMan*>(b->getGame());
        switch (direction)
        {
        case 0:
            b->setContent('<');
            if(!g->game_map[b->getY()-g->offsetY][b->getX()-g->offsetX-1] || !g->game_map[b->getY()-g->offsetY][b->getX()-g->offsetX-1]->isWall()){
                
            }
            break;
        case 1:
            b->setContent('v');
            if(!g->game_map[b->getY()-g->offsetY+1][b->getX()-g->offsetX]|| !g->game_map[b->getY()-g->offsetY][b->getX()-g->offsetX-1]->isWall()){
                
            }
            break;
        case 2:
            b->setContent('>');
            if(!g->game_map[b->getY()-g->offsetY][b->getX()-g->offsetX+1] || !g->game_map[b->getY()-g->offsetY][b->getX()-g->offsetX-1]->isWall()){
                
            }
            break;
        case 3:
            b->setContent('^');
            if(!g->game_map[b->getY()-g->offsetY-1][b->getX()-g->offsetX] || !g->game_map[b->getY()-g->offsetY][b->getX()-g->offsetX-1]->isWall()){
                
            }
            break;
        default:
            break;
        }

    }
}