#include "../AGE/player.h"
using namespace GameEngine;
class Chara : public Player {
    bool alive;
    int direction; // 0: <, 1:v, 2:>, 3: ^
    int speed;
public:
    Chara(int x, int y);
    void update(int input);
    bool is_alive () const;
    void kill();
};