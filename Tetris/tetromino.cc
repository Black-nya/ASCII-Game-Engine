#include "tetromino.h"
#include "block.h"
#include "tetris.h"
#include "util.h"
#include "../AGE/movement.h"

using namespace GameEngine;
Tetromino::Tetromino(Tetris *t, int color) : Compound{{}, t}, t{t}, color{color}
{
    addMovement(new Gravitating(Border::Down));
}

void Tetromino::release()
{
    clearMovement(); // remove all the movements
    Tetris *t = dynamic_cast<Tetris *>(game);
    for (Character *chara : contents)
    {
        game->addEntity(dynamic_cast<Block*>(chara));
        t->grid[chara->getY()][chara->getX()] = dynamic_cast<Block *>(chara);
    }
}
I::I(Tetris *t, int color) : Tetromino{t, color}
{

    if (getRandom(0, 1) == 0)
    {
        // vertical
        int minx = getRandom(1, t->width); // 1-78

        std::get<0>(bound) = std::get<1>(bound) = minx;
        std::get<2>(bound) = 1;
        std::get<3>(bound) = 4;
        for (int y = 1; y <= 4; y++)
        {
            contents.push_back(new Block{minx, y, color});
        }
        rotation = 1;
    }
    else
    {
        // horizontal
        int minx = getRandom(1, t->width - 3); // 1-75
        std::get<0>(bound) = minx;
        std::get<1>(bound) = minx + 3;
        std::get<2>(bound) = std::get<3>(bound) = 1;
        for (int x = minx; x <= minx + 3; x++)
        {
            contents.push_back(new Block(x, 1, color));
        }
        rotation = 0;
    }
}
void I::rotate()
{
    Tetris *g = dynamic_cast<Tetris *>(getGame());
    auto [a, b, c, d] = bound;
    switch (rotation)
    {
    case 0:

        if (c > 1 && c + 2 <= g->getHeight())
        {
            for (int row = c - 1; row <= c + 2; row++)
            {
                if (g->grid[row][a + 1])
                    return;
            }
            int row = c - 1;
            for (auto content : contents)
            {
                content->setX(a + 1);
                content->setY(row++);
            }

            std::get<0>(bound) = std::get<1>(bound) = a + 1;
            std::get<2>(bound) = c - 1;
            std::get<3>(bound) = c + 2;
            rotation = 1;
        }

        break;
    case 1:
        if (a > 1 && a + 2 <= g->getWidth())
        {
            for (int col = a - 1; col <= a + 2; col++)
            {
                if (g->grid[c + 2][col])
                    return;
            }
            int col = a - 1;
            for (auto content : contents)
            {
                content->setX(col++);
                content->setY(c + 2);
            }
            std::get<0>(bound) = a - 1;
            std::get<1>(bound) = a + 2;
            std::get<2>(bound) = std::get<3>(bound) = c + 2;
            rotation = 2;
        }
        break;
    case 2:
        if (c > 2 && c + 1 <= g->getHeight())
        {
            for (int row = c - 2; row <= c + 1; row++)
            {
                if (g->grid[row][a + 2])
                    return;
            }
            int row = c - 2;
            for (auto content : contents)
            {
                content->setX(a + 2);
                content->setY(row++);
            }

            std::get<0>(bound) = std::get<1>(bound) = a + 2;
            std::get<2>(bound) = c - 2;
            std::get<3>(bound) = c + 1;
            rotation = 3;
        }
        break;
    case 3:
        if (a > 2 && a + 1 <= g->getWidth())
        {
            for (int col = a - 2; col <= a + 1; col++)
            {
                if (g->grid[c + 1][col])
                    return;
            }
            int col = a - 2;
            for (auto content : contents)
            {
                content->setX(col++);
                content->setY(c + 1);
            }
            std::get<0>(bound) = a - 2;
            std::get<1>(bound) = a + 1;
            std::get<2>(bound) = std::get<3>(bound) = c + 1;
            rotation = 0;
        }
        break;
    default:
        break;
    }
}
O::O(Tetris *t, int color) : Tetromino{t, color}
{
    int minx = getRandom(1, t->width - 1); // 1-77
    std::get<0>(bound) = minx;
    std::get<1>(bound) = minx + 1;
    std::get<2>(bound) = 1;
    std::get<3>(bound) = 2;
    for (int x = minx; x <= minx + 1; x++)
    {
        for (int y = 1; y <= 2; y++)
        {
            contents.push_back(new Block(x, y, color));
        }
    }
}

T::T(Tetris *t, int color) : Tetromino{t, color}
{
    int minx = -1;
    switch (rotation = getRandom(0, 3))
    {
    case 0:
        // ...
        //  .
        minx = getRandom(1, t->width - 2);
        std::get<0>(bound) = minx;
        std::get<1>(bound) = minx + 2;
        std::get<2>(bound) = 1;
        std::get<3>(bound) = 2;
        for (int x = minx; x <= minx + 2; x++)
        {
            contents.push_back(new Block(x, 1, color));
        }
        contents.push_back(new Block(minx + 1, 2, color));
        break;
    case 1:
        // .
        // ..
        // .
        minx = getRandom(1, t->width - 1);
        std::get<0>(bound) = minx;
        std::get<1>(bound) = minx + 1;
        std::get<2>(bound) = 1;
        std::get<3>(bound) = 3;
        for (int y = 1; y <= 3; y++)
        {
            contents.push_back(new Block(minx, y, color));
        }
        contents.push_back(new Block(minx + 1, 2, color));
        break;
    case 2:
        //  .
        // ...
        minx = getRandom(1, t->width - 2);
        std::get<0>(bound) = minx;
        std::get<1>(bound) = minx + 2;
        std::get<2>(bound) = 1;
        std::get<3>(bound) = 2;
        for (int x = minx; x <= minx + 2; x++)
        {
            contents.push_back(new Block(x, 2, color));
        }
        contents.push_back(new Block(minx + 1, 1, color));
        break;
    case 3:
        // .
        //..
        // .
        minx = getRandom(1, t->width - 1);
        std::get<0>(bound) = minx;
        std::get<1>(bound) = minx + 1;
        std::get<2>(bound) = 1;
        std::get<3>(bound) = 3;
        for (int y = 1; y <= 3; y++)
        {
            contents.push_back(new Block(minx + 1, y, color));
        }
        contents.push_back(new Block(minx, 2, color));
        break;
    }
}
void T::rotate()
{
    Tetris *g = dynamic_cast<Tetris *>(getGame());
    auto [a, b, c, d] = bound;
    switch (rotation)
    {
    case 0:
        if (c > 1)
        {
            if (g->grid[c - 1][a + 1])
                return;
            for (auto content : contents)
            {
                if (content->getX() == a)
                {
                    content->setX(a + 1);
                    content->setY(c - 1);
                    break;
                }
            }
            std::get<0>(bound) += 1; // minx += 1
            std::get<2>(bound) -= 1; // miny -= 1
            rotation = 1;
        }

        break;
    case 1:
        if (a > 1)
        {
            if (g->grid[c + 1][a - 1])
                return;
            for (auto content : contents)
            {
                if (content->getY() == d)
                {
                    content->setX(a - 1);
                    content->setY(c + 1);
                    break;
                }
            }
            std::get<0>(bound) -= 1; // minx-=1
            std::get<3>(bound) -= 1; // maxy-=1
            rotation = 2;
        }
        break;
    case 2:
        if (d < g->getHeight())
        {
            if (g->grid[d + 1][a + 1])
                return;
            for (auto content : contents)
            {
                if (content->getX() == b)
                {
                    content->setX(a + 1);
                    content->setY(d + 1);
                    break;
                }
            }
            std::get<3>(bound) += 1; // maxy +=1
            std::get<1>(bound) -= 1; // maxx -=1
            rotation = 3;
        }
        break;
    case 3:
        if (b < g->getWidth())
        {
            if (g->grid[c + 1][b + 1])
                return;
            for (auto content : contents)
            {
                if (content->getY() == c)
                {
                    content->setX(b + 1);
                    content->setY(c + 1);
                    break;
                }
            }
            std::get<2>(bound) += 1; // miny +=1
            std::get<1>(bound) += 1; // maxx +=1
            rotation = 0;
        }
        break;
    default:
        break;
    }
}
L::L(Tetris *t, int color) : Tetromino{t, color}
{
    int minx = -1;
    switch (rotation = getRandom(0, 3))
    {
    case 0:
        // .
        // .
        // ..
        minx = getRandom(1, t->width - 1);
        std::get<0>(bound) = minx;
        std::get<1>(bound) = minx + 1;
        std::get<2>(bound) = 1;
        std::get<3>(bound) = 3;
        for (int y = 1; y <= 3; y++)
        {
            contents.push_back(new Block(minx, y, color));
        }
        contents.push_back(new Block(minx + 1, 3, color));
        break;
    case 1:
        //   .
        // ...
        minx = getRandom(1, t->width - 2);
        std::get<0>(bound) = minx;
        std::get<1>(bound) = minx + 2;
        std::get<2>(bound) = 1;
        std::get<3>(bound) = 2;
        for (int x = minx; x <= minx + 2; x++)
        {
            contents.push_back(new Block(x, 2, color));
        }
        contents.push_back(new Block(minx + 2, 1, color));
        break;
    case 2:
        // ..
        //  .
        //  .
        minx = getRandom(1, t->width - 1);
        std::get<0>(bound) = minx;
        std::get<1>(bound) = minx + 1;
        std::get<2>(bound) = 1;
        std::get<3>(bound) = 3;
        for (int y = 1; y <= 3; y++)
        {
            contents.push_back(new Block(minx + 1, y, color));
        }
        contents.push_back(new Block(minx, 1, color));
        break;
    case 3:
        // ...
        // .
        minx = getRandom(1, t->width - 2);
        std::get<0>(bound) = minx;
        std::get<1>(bound) = minx + 2;
        std::get<2>(bound) = 1;
        std::get<3>(bound) = 2;
        for (int x = minx; x <= minx + 2; x++)
        {
            contents.push_back(new Block(x, 1, color));
        }
        contents.push_back(new Block(minx, 2, color));
        break;
    }
}
void L::rotate()
{
    Tetris *g = dynamic_cast<Tetris *>(getGame());
    auto &[minx, maxx, miny, maxy] = bound;
    switch (rotation)
    {
    case 0:
        if (minx > 1)
        {
            if (g->grid[maxy - 1][minx - 1] || g->grid[maxy - 1][maxx] || g->grid[miny][maxx])
                return;
            minx -= 1;
            maxy -= 1;
            int id = 0;
            for (; id<3; id++)
            {
                contents[id]->setX(minx+id);
                contents[id]->setY(maxy);
            }
            contents[id]->setX(maxx);
            contents[id]->setY(miny);
            rotation = 1;
        }
        break;
    case 1:
        if (maxy < g->getHeight())
        {
            if (g->grid[miny][minx] || g->grid[miny][minx+1] || g->grid[maxy+1][minx+1])
                return;
            maxx -= 1;
            maxy += 1;
            int id = 0;
            for (; id<3; id++)
            {
                contents[id]->setX(maxx);
                contents[id]->setY(miny+id);
            }
            contents[id]->setX(minx);
            contents[id]->setY(miny);
            rotation = 2;
        }
        break;
    case 2:
        if (maxx < g->getWidth())
        {
            if (g->grid[miny+1][minx] || g->grid[maxy][minx] || g->grid[miny+1][maxx+1])
                return;
            miny += 1;
            maxx += 1;
            int id = 0;
            for (; id<3; id++)
            {
                contents[id]->setX(minx+id);
                contents[id]->setY(miny);
            }
            contents[id]->setX(minx);
            contents[id]->setY(maxy);
            rotation = 3;
        }
        break;
    case 3:
        if (miny > 1)
        {
            if (g->grid[miny - 1][minx + 1] || g->grid[maxy ][minx+1] || g->grid[maxy][maxx])
                return;
            miny -= 1;
            minx += 1;
            int id = 0;
            for (; id<3; id++)
            {
                contents[id]->setX(minx);
                contents[id]->setY(miny+id);
            }
            contents[id]->setX(maxx);
            contents[id]->setY(maxy);
            rotation = 0;
        }
        break;
    default:
        break;
    }
}
J::J(Tetris *t, int color) : Tetromino{t, color}
{
    int minx = -1;
    switch (rotation = getRandom(0, 3))
    {
    case 0:
        // .
        // .
        //..
        minx = getRandom(1, t->width - 1);
        std::get<0>(bound) = minx;
        std::get<1>(bound) = minx + 1;
        std::get<2>(bound) = 1;
        std::get<3>(bound) = 3;
        for (int y = 1; y <= 3; y++)
        {
            contents.push_back(new Block(minx + 1, y, color));
        }
        contents.push_back(new Block(minx, 3, color));
        break;
    case 1:
        // ...
        //   .
        minx = getRandom(1, t->width - 2);
        std::get<0>(bound) = minx;
        std::get<1>(bound) = minx + 2;
        std::get<2>(bound) = 1;
        std::get<3>(bound) = 2;
        for (int x = minx; x <= minx + 2; x++)
        {
            contents.push_back(new Block(x, 1, color));
        }
        contents.push_back(new Block(minx + 2, 2, color));
        break;
    case 2:
        // ..
        // .
        // .
        minx = getRandom(1, t->width - 1);
        std::get<0>(bound) = minx;
        std::get<1>(bound) = minx + 1;
        std::get<2>(bound) = 1;
        std::get<3>(bound) = 3;
        for (int y = 1; y <= 3; y++)
        {
            contents.push_back(new Block(minx, y, color));
        }
        contents.push_back(new Block(minx + 1, 1, color));
        break;
    case 3:
        //.
        //...
        minx = getRandom(1, t->width - 2);
        std::get<0>(bound) = minx;
        std::get<1>(bound) = minx + 2;
        std::get<2>(bound) = 1;
        std::get<3>(bound) = 2;
        for (int x = minx; x <= minx + 2; x++)
        {
            contents.push_back(new Block(x, 2, color));
        }
        contents.push_back(new Block(minx, 1, color));
        break;
    }
}
void J::rotate()
{
    Tetris *g = dynamic_cast<Tetris *>(getGame());
    auto &[minx, maxx, miny, maxy] = bound;
    switch (rotation)
    {
    case 0:
        if (maxx < g->getWidth())
        {
            if (g->grid[maxy - 1][minx] || g->grid[maxy - 1][maxx+1] || g->grid[maxy][maxx+1])
                return;
            maxx += 1;
            miny += 1;
            int id = 0;
            for (; id<3; id++)
            {
                contents[id]->setX(minx+id);
                contents[id]->setY(miny);
            }
            contents[id]->setX(maxx);
            contents[id]->setY(maxy);
            rotation = 1;
        }
        break;
    case 1:
        if (miny > 1)
        {
            if (g->grid[miny-1][maxx] || g->grid[miny-1][maxx-1] || g->grid[maxy][minx+1])
                return;
            miny -= 1;
            minx += 1;
            int id = 0;
            for (; id<3; id++)
            {
                contents[id]->setX(minx);
                contents[id]->setY(miny+id);
            }
            contents[id]->setX(maxx);
            contents[id]->setY(miny);
            rotation = 2;
        }
        break;
    case 2:
        if (minx >1)
        {
            if (g->grid[miny][minx-1] || g->grid[miny+1][minx-1] || g->grid[miny+1][maxx])
                return;
            maxy -= 1;
            minx -= 1;
            int id = 0;
            for (; id<3; id++)
            {
                contents[id]->setX(minx+id);
                contents[id]->setY(maxy);
            }
            contents[id]->setX(minx);
            contents[id]->setY(miny);
            rotation = 3;
        }
        break;
    case 3:
        if (maxy < g->getHeight())
        {
            if (g->grid[miny][minx + 1] || g->grid[maxy+1 ][minx+1] || g->grid[maxy+1][minx])
                return;
            maxy += 1;
            maxx -= 1;
            int id = 0;
            for (; id<3; id++)
            {
                contents[id]->setX(maxx);
                contents[id]->setY(miny+id);
            }
            contents[id]->setX(minx);
            contents[id]->setY(maxy);
            rotation = 0;
        }
        break;
    default:
        break;
    }
}
S::S(Tetris *t, int color) : Tetromino{t, color}
{

    if (getRandom(0, 1) == 0)
    {
        // ..
        //..
        int minx = getRandom(1, t->width - 2);
        std::get<0>(bound) = minx;
        std::get<1>(bound) = minx + 2;
        std::get<2>(bound) = 1;
        std::get<3>(bound) = 2;
        contents.push_back(new Block(minx, 2, color));
        contents.push_back(new Block(minx + 1, 2, color));
        contents.push_back(new Block(minx + 1, 1, color));
        contents.push_back(new Block(minx + 2, 1, color));
        rotation = 0;
    }
    else
    {
        // .
        // ..
        //  .
        int minx = getRandom(1, t->width - 1);
        std::get<0>(bound) = minx;
        std::get<1>(bound) = minx + 1;
        std::get<2>(bound) = 1;
        std::get<3>(bound) = 3;
        contents.push_back(new Block(minx, 1, color));
        contents.push_back(new Block(minx, 2, color));
        contents.push_back(new Block(minx + 1, 2, color));
        contents.push_back(new Block(minx + 1, 3, color));
        rotation = 1;
    }
}
void S::rotate()
{
    Tetris *g = dynamic_cast<Tetris *>(getGame());
    auto &[minx, maxx, miny, maxy] = bound;
    switch (rotation)
    {
    case 0:
        if (maxy < g->getHeight())
        {
            if (g->grid[miny][minx] || g->grid[maxy + 1][maxx - 1])
                return;
            maxx -= 1;
            maxy += 1;
            for (auto content : contents)
            {
                delete content;
            }
            contents.clear();
            contents.push_back(new Block(minx, miny, color));
            contents.push_back(new Block(minx, miny + 1, color));
            contents.push_back(new Block(minx + 1, miny + 1, color));
            contents.push_back(new Block(minx + 1, maxy, color));
            rotation = 1;
        }
        break;
    case 1:
        if (maxx < g->getWidth())
        {
            if (g->grid[maxy][minx] || g->grid[miny + 1][maxx + 1])
                return;
            maxx += 1;
            miny += 1;
            for (auto content : contents)
            {
                delete content;
            }
            contents.clear();
            contents.push_back(new Block(minx, maxy, color));
            contents.push_back(new Block(minx + 1, maxy, color));
            contents.push_back(new Block(minx + 1, miny, color));
            contents.push_back(new Block(maxx, miny, color));
            rotation = 2;
        }
        break;
    case 2:
        if (miny > 1)
        {
            if (g->grid[miny - 1][minx + 1] || g->grid[maxy][maxx])
                return;
            minx += 1;
            miny -= 1;
            for (auto content : contents)
            {
                delete content;
            }
            contents.clear();
            contents.push_back(new Block(minx, miny, color));
            contents.push_back(new Block(minx, miny + 1, color));
            contents.push_back(new Block(maxx, miny + 1, color));
            contents.push_back(new Block(maxx, maxy, color));
            rotation = 3;
        }
        break;
    case 3:
        if (minx > 1)
        {
            if (g->grid[maxy - 1][minx - 1] || g->grid[miny][maxx])
                return;
            minx -= 1;
            maxy -= 1;
            for (auto content : contents)
            {
                delete content;
            }
            contents.clear();
            contents.push_back(new Block(minx, maxy, color));
            contents.push_back(new Block(minx + 1, maxy, color));
            contents.push_back(new Block(minx + 1, miny, color));
            contents.push_back(new Block(maxx, miny, color));
            rotation = 0;
        }
        break;
    default:
        break;
    }
}
Z::Z(Tetris *t, int color) : Tetromino{t, color}
{
    if (getRandom(0, 1) == 0)
    {
        // ..
        //  ..
        int minx = getRandom(1, t->width - 2);
        std::get<0>(bound) = minx;
        std::get<1>(bound) = minx + 2;
        std::get<2>(bound) = 1;
        std::get<3>(bound) = 2;
        contents.push_back(new Block(minx, 1, color));
        contents.push_back(new Block(minx + 1, 1, color));
        contents.push_back(new Block(minx + 1, 2, color));
        contents.push_back(new Block(minx + 2, 2, color));
        rotation = 0;
    }
    else
    {
        // .
        //..
        //.
        int minx = getRandom(1, t->width - 1);
        std::get<0>(bound) = minx;
        std::get<1>(bound) = minx + 1;
        std::get<2>(bound) = 1;
        std::get<3>(bound) = 3;
        contents.push_back(new Block(minx, 3, color));
        contents.push_back(new Block(minx, 2, color));
        contents.push_back(new Block(minx + 1, 2, color));
        contents.push_back(new Block(minx + 1, 1, color));
        rotation = 1;
    }
}
void Z::rotate()
{
    Tetris *g = dynamic_cast<Tetris *>(getGame());
    auto &[minx, maxx, miny, maxy] = bound;
    switch (rotation)
    {
    case 0:
        if (maxy < g->getHeight())
        {
            if (g->grid[maxy][minx] || g->grid[maxy + 1][minx])
                return;
            maxy += 1;
            maxx -= 1;
            for (auto content : contents)
            {
                delete content;
            }
            contents.clear();
            contents.push_back(new Block(minx, maxy, color));
            contents.push_back(new Block(minx, maxy - 1, color));
            contents.push_back(new Block(minx + 1, maxy - 1, color));
            contents.push_back(new Block(minx + 1, miny, color));
            rotation = 1;
        }
        break;
    case 1:
        if (maxx < g->getWidth())
        {
            if (g->grid[maxy][maxx + 1] || g->grid[maxy][maxx])
                return;
            maxx += 1;
            miny += 1;
            for (auto content : contents)
            {
                delete content;
            }
            contents.clear();
            contents.push_back(new Block(minx, miny, color));
            contents.push_back(new Block(minx + 1, miny, color));
            contents.push_back(new Block(minx + 1, maxy, color));
            contents.push_back(new Block(maxx, maxy, color));
            rotation = 2;
        }
        break;
    case 2:
        if (miny > 1)
        {
            if (g->grid[miny - 1][maxx] || g->grid[miny][maxx])
                return;
            minx += 1;
            miny -= 1;
            for (auto content : contents)
            {
                delete content;
            }
            contents.clear();
            contents.push_back(new Block(minx, maxy, color));
            contents.push_back(new Block(minx, maxy - 1, color));
            contents.push_back(new Block(maxx, miny + 1, color));
            contents.push_back(new Block(maxx, miny, color));
            rotation = 3;
        }
        break;
    case 3:
        if (minx > 1)
        {
            if (g->grid[miny][minx - 1] || g->grid[miny][minx])
                return;
            minx -= 1;
            maxy -= 1;
            for (auto content : contents)
            {
                delete content;
            }
            contents.clear();
            contents.push_back(new Block(minx, miny, color));
            contents.push_back(new Block(minx + 1, miny, color));
            contents.push_back(new Block(maxx - 1, maxy, color));
            contents.push_back(new Block(maxx, maxy, color));
            rotation = 0;
        }
        break;
    default:
        break;
    }
}