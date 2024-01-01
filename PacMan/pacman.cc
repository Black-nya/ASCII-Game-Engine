#include "pacman.h"
#include "cell.h"
#include "../AGE/constants.h"
#include "chara.h"
#include <fstream>
PacMan::PacMan(const std::string& mapname):Game{BorderType::Solid}{
    std::ifstream f{mapname};
    
    if(f.is_open()){
        std::string line;
        int row = 0;
        while(getline(f,line)){
            std::vector<Cell*> temp;
            for(size_t col=0; col<line.size(); col++){
                switch (line[col])
                {
                case ' ':
                    temp.push_back(new Cell{col, row, '.', 3, false});  // dots
                    break;
                case '#':
                    temp.push_back(new Cell(col, row, ' ', 1, true));  // walls
                    break;
                case 'o':
                    temp.push_back(nullptr);
                    // spawn location of the enemy
                    enemy_spawn_locations.push_back({col,row});
                    break;
                case 'S':
                    temp.push_back(nullptr);
                    // spawn location of the player
                    chara_spawn_location = {col, row};
                    break;
                default:
                    // O_o o_O
                    // debug << line[col] << " " << col << std::endl;
                    throw "Unrecognized Element!";
                    break;
                }
            }
            row++;
            game_map.push_back(temp);
        }
        f.close();
        // go fix the offsets   
        using GameEngine::GAME_HEIGHT; // 22
        using GameEngine::WINDOW_WIDTH; // 80
        offsetY = (GAME_HEIGHT-row)/2;
        offsetX = (WINDOW_WIDTH-game_map[0].size())/2;
        for(auto & row: game_map){
            for(Cell* cell: row){
                if(cell){
                    cell->setX(cell->getX()+offsetX);
                    cell->setY(cell->getY()+offsetY);
                    addEntity(cell);
                }
            }
        }
        player = new Chara{chara_spawn_location.first+offsetX,chara_spawn_location.second+offsetY};
    }else{
        throw InvalidMap{};
    }
}