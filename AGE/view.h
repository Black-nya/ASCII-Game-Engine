#include <memory>
#include <curses.h>
namespace GameEngine
{
    class Game;
    class Controller;
    class View
    {
    public:
        virtual void render(const Game &game) const = 0;
        virtual void renderStatus(const Game &game) const = 0;
    };
    
    class TerminalView : public View
    {
        WINDOW *playground;
        WINDOW *status;

    public:
        TerminalView();
        void render(const Game& game) const override;
        void renderStatus(const Game& game) const override;
    };
}