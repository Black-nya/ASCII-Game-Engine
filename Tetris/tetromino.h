#ifndef _TETROMINO_
#define _TETROMINO_
#include "../AGE/entity.h"
#include <tuple>
using namespace GameEngine;
class Tetris;
class Tetromino : public Compound
{
    
    Tetris* t;
    
protected:
    int rotation; // 0,1,2,3
    int color;
    Tetromino(Tetris *t, int color);
public:
    int tick = 5; // 
    int cur = 0;
    void release(); // release this tetromino into 4 blocks
    virtual void rotate() = 0;  // rotate the tetromino counter clockwise by 90
};
class I : public Tetromino
{
    
    // ....
public:
    I(Tetris *t, int color);
    void rotate() override;
};
class O : public Tetromino
{
    // ..
    // ..
public:
    O(Tetris *t, int color);
    void rotate() override{}

};
class T : public Tetromino
{
    // ...
    //  .
public:
    T(Tetris *t, int color);
    void rotate() override;
};
class L : public Tetromino
{
    // .
    // .
    // ..
public:
    L(Tetris *t, int color);
    void rotate() override;
};
class J : public Tetromino
{
    // .
    // .
    //..
public:
    J(Tetris *t, int color);
    void rotate() override;
};
class S : public Tetromino
{
    // ..
    //..
public:
    S(Tetris *t, int color);
    void rotate() override;
};
class Z : public Tetromino
{
    //..
    // ..
public:
    Z(Tetris *t, int color);
    void rotate() override;
};
#endif