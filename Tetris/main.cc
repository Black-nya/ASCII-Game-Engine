#include "../AGE/age.h"
#include "tetris.h"
using namespace GameEngine;
int main(){
    std::shared_ptr<Tetris> game = std::make_shared<Tetris>();
    Model model(std::make_unique<TerminalView>(),std::make_unique<KeyboardController>(),game);
    model.go();
    return 0;
}