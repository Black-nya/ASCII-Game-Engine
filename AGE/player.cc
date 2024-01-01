#include "player.h"
#include "entity.h"
#include "game.h"
#include "movement.h"
namespace GameEngine
{
    Player::Player(Entity *entity) : entity{entity}
    {
        entity->player = true;
    }
    void Player::update(int input)
    {   if(entity){
            
            Move *temp = nullptr;
            if (Character *t = dynamic_cast<Character *>(entity))
            {
                switch (input)
                {
                case 'w':
                    if(t->getY()>1)
                        temp = new Move{0, -1};
                    break;
                case 's':
                    if(t->getY()<t->getGame()->height)
                        temp = new Move{0, 1};
                    break;
                case 'd':
                    if(t->getX()<t->getGame()->width)
                        temp = new Move{1, 0};
                    break;
                case 'a':
                    if(t->getX()>1)
                        temp = new Move{-1, 0};
                    break;
                default:
                    return;
                }
            }
            else if (Compound *t = dynamic_cast<Compound *>(entity))
            {
                auto [minx, maxx, miny, maxy] = t->bound;
                switch (input)
                {
                case 'w':
                    if(miny>1)
                        temp = new Move{0, -1};
                    break;
                case 's':
                    if(maxy<t->getGame()->height)
                        temp = new Move{0, 1};
                    break;
                case 'd':
                    if(maxx<t->getGame()->width)
                        temp = new Move{1, 0};
                    break;
                case 'a':
                    if(minx>1)
                        temp = new Move{-1, 0};
                    break;
                default:
                    return;
                }
            }
            if(temp){
                entity->addMovement(temp);
                entity->update();
                entity->deleteMovement(temp);
                delete temp;
            }else{
                entity->update();
            }
        }  
    }
}