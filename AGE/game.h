#ifndef _GAME_
#define _GAME_
#include <vector>

namespace GameEngine
{
    class Entity;
    class Player;
    class CollisionInfo;
    class OutofBound;
    class Game
    {
    protected: 
        bool end;
    public:
        enum class BorderType
        {
            Solid, // objects is bounded
            View   // objects is not bounded
        };
        BorderType border;
        Player *player = nullptr;       // the player controlled entity
        std::vector<Entity *> entities; // the list of entities, excluding player
        int width = 78;
        int height = 20;
        Game(BorderType type) : end{false},border{type} {}
        virtual const int getWidth() const { return width; }
        virtual const int getHeight() const { return height; }
        void runOnce(int input);
        void addEntity(Entity *entity);
        void destroyEntity(Entity *entity);
        void setPlayer(Player *player) { this->player = player; }
        virtual void collisionHandler(std::vector<std::vector<CollisionInfo>> &);
        virtual void outOfBoundHandler(std::vector<std::vector<OutofBound>> &);
        inline const bool over() const
        {
            return end;
        }
    };
}
#endif