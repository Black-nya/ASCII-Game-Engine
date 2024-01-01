#ifndef _PACMAN_
#define _PACMAN_
#include "../AGE/game.h"
#include "../AGE/entity.h"
#include <string>
using GameEngine::Game;
using GameEngine::Character;
class InvalidMap{};
class Cell;
class PacMan : public Game{
    
    
    std::vector<std::pair<int,int>> enemy_spawn_locations;
    std::pair<int,int> chara_spawn_location;
public:
    std::vector<std::vector<Cell*>> game_map;
    int offsetX, offsetY; // offset from the screen
    PacMan(const std::string&);
};
#endif