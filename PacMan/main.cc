#include "../AGE/age.h"
#include "pacman.h"
using namespace GameEngine;
int main(){
    std::shared_ptr<PacMan> game = std::make_shared<PacMan>("PacMan/map.txt");
    Model model(std::make_unique<TerminalView>(),std::make_unique<KeyboardController>(),game);
    model.go();
    return 0;
}