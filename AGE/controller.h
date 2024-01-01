#include <curses.h>
namespace GameEngine
{
    class Controller
    {
    public:
        virtual const int getInput() const = 0;
    };

    class KeyboardController : public Controller
    {
    public:
        const int getInput() const override
        {
            return getch();
        }
    };
}