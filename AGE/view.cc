#include <chrono>
#include <thread>
#include "view.h"
#include "game.h"
#include "constants.h"
#include "entity.h"
#include "player.h"
namespace GameEngine
{
    TerminalView::TerminalView()
    {
        setlocale(LC_ALL, "");
        initscr();
        cbreak();
        noecho();
        if (has_colors())
            start_color();
        init_pair(0, COLOR_CYAN, COLOR_BLACK);
        init_pair(1, COLOR_BLUE, COLOR_BLACK);
        init_pair(2, COLOR_WHITE, COLOR_BLACK);
        init_pair(3, COLOR_YELLOW, COLOR_BLACK);
        init_pair(4, COLOR_GREEN, COLOR_BLACK);
        init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(6, COLOR_RED, COLOR_BLACK);
        keypad(stdscr, true);
        curs_set(0);
        nodelay(stdscr, true);
        playground = newwin(GAME_HEIGHT, WINDOW_WIDTH, 0, 0);
        status = newwin(STATUS_HEIGHT, WINDOW_WIDTH, 23, 0);
        refresh();
        box(playground, 0, 0);
        wrefresh(playground);
        wrefresh(status);
    }
    void TerminalView::render(const Game &game) const
    {
        wclear(playground);
        box(playground, 0, 0);
        bool playerdisplay = false;
        for (Entity *entity : game.entities)
        {
            if (!playerdisplay && game.player && game.player->entity && entity->getZ() > game.player->entity->getZ())
            {
                game.player->entity->draw(playground);
                playerdisplay = true;
            }
            entity->draw(playground);
        }
        if (!playerdisplay && game.player && game.player->entity){
            game.player->entity->draw(playground);
        }
        wrefresh(playground);
        wrefresh(status);
    }
    void TerminalView::renderStatus(const Game&game) const{
        
    }
}