#ifndef _MOVEMENT_
#define _MOVEMENT_
#include "movement.h"
#include "entity.h"
namespace GameEngine{
    void Move::transform(Character& chara){
        chara.setX(chara.getX()+dir.first);
        chara.setY(chara.getY()+dir.second);
    }
    void Move::transform(Compound& comp){
        for(Character* chara: comp.contents){
            transform(*chara);
        }
        comp.centerx += dir.first;
        std::get<0>(comp.bound) += dir.first;
        std::get<1>(comp.bound) += dir.first;
        comp.centery += dir.second;
        std::get<2>(comp.bound) += dir.second;
        std::get<3>(comp.bound) += dir.second;
        
    }
    void Scale::transform(Character& chara){
        
    }

    void Scale::transform(Compound& comp){
        
    }

    void Teleport::transform(Character& chara){
        chara.setX(x);
        chara.setY(y);
    }

    void Teleport::transform(Compound& comp){
        int dx = x-comp.getX();
        int dy = y-comp.getY();
        comp.setX(x);
        comp.setY(y);
        Move temp{dx, dy};
        for(Character* chara: comp.contents){
            temp.transform(*chara);
        }
        std::get<0>(comp.bound) += dx;
        std::get<1>(comp.bound) += dx;
        std::get<2>(comp.bound) += dy;
        std::get<3>(comp.bound) += dy;
    }

    void Complex::transform(Character& chara){
        if (i == moves.size())
            i=0;
        if (moves.size() > 0){
            moves[i++]->transform(chara);
        }
    }

    void Complex::transform(Compound& comp){
        if (i == moves.size())
            i=0;
        if (moves.size() > 0){
            moves[i++]->transform(comp);
        }
    }
}
#endif