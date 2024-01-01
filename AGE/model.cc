#ifndef _MODEL_
#define _MODEL_
#include "model.h"
#include "game.h"
#include "controller.h"
#include "view.h"
#include <thread>

#include "constants.h"
namespace GameEngine
{
    void Model::go(){
        extern const std::chrono::milliseconds rate;
        
        while (!game->over())
        {   
            view->render(*game);
            game->runOnce(controller->getInput());
            std::this_thread::sleep_for(rate);
        }
        end();   
    }
    void Model::end(){
        endwin();
    }
} // namespace GameEngine
#endif