#ifndef _PLAYER_
#define _PLAYER_
namespace GameEngine
{
    class Entity;
    class Player
    {

    public:
        Entity *entity;
        Player(Entity *entity);
        virtual void update(int input);
        virtual void setPlayer(Entity *entity)
        {
            this->entity = entity;
        }
    };
}
#endif