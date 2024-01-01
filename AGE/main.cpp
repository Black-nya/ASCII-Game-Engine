#include "age.h"
int main(int argc, char *argv[]){
    std::shared_ptr<GameEngine::Game> game = std::make_shared<GameEngine::Game>(GameEngine::Game::BorderType::Solid);
    GameEngine::Model model(std::make_unique<GameEngine::TerminalView>(),std::make_unique<GameEngine::KeyboardController>(),game);
    
    GameEngine::Character* chara = new GameEngine::Character(1,1,'m');
    GameEngine::Gravitating* move1 = new GameEngine::Gravitating(GameEngine::Border::Down);
    GameEngine::Move* move2 = new GameEngine::Move(1,1);
    GameEngine::Straight* move3 = new GameEngine::Straight(60,23);
    GameEngine::Teleport* move4 = new GameEngine::Teleport(2,4);
    GameEngine::Rectangle* box = new GameEngine::Rectangle(4,5,4,6,'z');
    std::vector<std::tuple<int,int,char>> temp = {{2,3,'l'},{3,4,'j'},{9, 10, 'y'}};
    GameEngine::BitMap* bm = new GameEngine::BitMap(temp);
    bm->z = 1;
    GameEngine::Player* player = new GameEngine::Player(box);
    box->setGame(game.get());
    game->setPlayer(player);
    chara->addMovement(move1);
    bm->addMovement(move4);
    game->addEntity(chara);
    game->addEntity(bm);
    model.go();
	endwin();
	return 0;
}