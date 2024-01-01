#include <memory>
namespace GameEngine
{
    class View;
    class Controller;
    class Game;
    class Model
    {
        std::unique_ptr<View> view;             // output
        std::unique_ptr<Controller> controller; // input
        std::shared_ptr<Game> game;             // internal game logic

    public:
        Model(std::unique_ptr<View> view, std::unique_ptr<Controller> controller, std::shared_ptr<Game> game) : view{std::move(view)}, controller{std::move(controller)}, game{std::move(game)} {}
        void go();
        void end(); // cleans up the memory it uses
    };
}