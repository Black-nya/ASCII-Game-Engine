#include "movement.h"
#include "entity.h"
#include "game.h"

namespace GameEngine
{
    void Character::update()
    {
        for (Movement *move : movements)
        {
            move->transform(*this);
        }
    }
    void Compound::update()
    {
        for (Movement *move : movements)
        {
            move->transform(*this);
        }
    }
    bool Character::inBounds()
    {
        return pos.getX() > 0 && pos.getX() < game->width + 1 && pos.getY() > 0 && pos.getY() < game->height + 1;
    }
    std::vector<OutofBound> Character::outofbound()
    {
        std::vector<OutofBound> res;
        if (getX() < 1 || getX() >= game->width || getY() < 1 || getY() >= game->height)
        {
            res.push_back(OutofBound{getX(), getY(), getZ(), this});
        }
        return res;
    }
    std::vector<OutofBound> Compound::outofbound()
    {
        std::vector<OutofBound> res;
        for (const auto &p : allPoints())
        {
            if (std::get<0>(p) < 1 || std::get<0>(p) >= game->width || std::get<1>(p) < 1 || std::get<1>(p) >= game->height)
            {
                res.push_back(OutofBound{std::get<0>(p), std::get<1>(p), std::get<2>(p), this});
            }
        }
        return res;
    }
    
}