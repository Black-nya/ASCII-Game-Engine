#ifndef _CONSTANTS_
#define _CONSTANTS_
#include <chrono>
namespace GameEngine{
    const int WINDOW_WIDTH = 80;
    const int WINDOW_HEIGHT = 25;
    const int GAME_HEIGHT = 22;
    const int STATUS_HEIGHT = 3;
    const int FPS = 20; // 20 fps
    using namespace std::chrono_literals;
    const std::chrono::milliseconds rate = 50ms;
}
#endif