#include "game.h"
#include "entity.h"
#include "player.h"
#include <algorithm>
namespace GameEngine
{
    void Game::runOnce(int input)
    {
        
        std::vector<std::vector<CollisionInfo>> collisions;
        std::vector<std::vector<OutofBound>> outofbounds;
        
        for (Entity* entity : entities)
        {
            entity->update();
        }
        if(player && player->entity) player->update(input);
        for (size_t i = 0; i < entities.size(); i++)
        {
            for (size_t j = i + 1; j < entities.size(); j++)
            {
                auto temp = entities[i]->overlap(entities[j]);
                if (!temp.empty())
                    collisions.push_back(temp);
            }
        }
        std::sort(entities.begin(),entities.end(),[](Entity* a, Entity* b){
            return a->getZ() < b->getZ();
        });
        collisionHandler(collisions);
        outOfBoundHandler(outofbounds);
    }
    void Game::addEntity(Entity *entity)
    {

        entities.push_back(entity);
        entity->setGame(this);
    }
    void Game::destroyEntity(Entity *entity)
    {
        entities.erase(std::find(entities.begin(), entities.end(), entity));
    }
    void Game::collisionHandler(std::vector<std::vector<CollisionInfo>> & collisions){

    }
    void Game::outOfBoundHandler(std::vector<std::vector<OutofBound>> & outofbounds){
        
    }
}