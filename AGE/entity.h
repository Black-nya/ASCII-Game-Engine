#ifndef _ENTITY_
#define _ENTITY_
#include <vector>
#include <tuple>
#include <numeric>
#include <algorithm>
#include <curses.h>
#include <fstream>
namespace GameEngine
{
    class Movement;
    class Game;
    class Entity;

    class CollisionInfo
    {
        int x, y, z;   // where the collision occurs
        Entity *a, *b; // the two entities that collide with each ohter
    public:
        CollisionInfo(int x, int y, int z, Entity *a, Entity *b) : x{x}, y{y}, z{z}, a{a}, b{b} {}
    };
    class OutofBound
    {
        int x, y, z; // where the collision occurs
        Entity *a;   // the entity that is out of bound
    public:
        OutofBound(int x, int y, int z, Entity *a) : x{x}, y{y}, z{z}, a{a} {}
    };
    class Entity
    {
    protected:
        std::vector<Movement *> movements; // the set of movements to be performed

        Entity(Game *game = nullptr) : game{game} {}
    public:
        virtual ~Entity(){}
        Game *game; // the game the entity is currently in
        bool player = false;
        void addMovement(Movement *movement) // add a movement
        {
            movements.push_back(movement);
        }
        void deleteMovement(Movement *movement) // erase a movement
        {
            movements.erase(std::find(movements.begin(), movements.end(), movement));
        }
        void clearMovement(){
            movements.clear();
        }
        virtual Game* getGame(){
            return game;
        }
        virtual void setGame(Game *game) = 0;                           // set the Game it is in
        virtual void draw(WINDOW *) = 0;                                // draw it in the gameboard if it is in bound
        virtual void update() = 0;                                      // update its position according to the movement it has
        
        virtual std::vector<CollisionInfo> overlap(Entity *) = 0;       // checks if it has a overlap with another entity
        virtual std::vector<std::tuple<int, int, int>> allPoints() = 0; // returns a list of points the entity occupies
        virtual std::vector<OutofBound> outofbound() = 0;               // returns a list of points that are out of bound
        

        virtual const int getX() const = 0;
        virtual const int getY() const = 0;
        virtual const int getZ() const = 0;

        virtual void setX(int) = 0;
        virtual void setY(int) = 0;
        virtual void setZ(int) = 0; 
    };
    class Character : public Entity
    {
    protected:
        char content;

    public:
        class Position // holds the position of a character
        {
            int x;
            int y;
            int z;
            Position(int x, int y, int z = 0) : x{x}, y{y}, z{z} {}

            inline const int getX() const { return x; }
            inline const int getY() const { return y; }
            inline const int getZ() const { return z; }
            inline void setX(int x) { this->x = x; }
            inline void setY(int y) { this->y = y; }
            inline void setZ(int z) { this->z = z; }

        public:
            friend class Character; // so that Character has access to Position's constructor
        };

    private:
        Position pos;    // the position of the character
        bool inBounds(); // checks if the character is inside the gameboard
    public:
        Character(int x, int y, char content, Game *game = nullptr) : Entity{game}, pos{x, y}, content{content} {}
        ~Character(){}
        virtual void draw(WINDOW *playground) override
        {
            if (inBounds()) mvwaddch(playground, pos.getY(), pos.getX(), content);
        }
        inline void setX(int x) override { pos.setX(x); }                      // set the x position of the character
        inline void setY(int y) override { pos.setY(y); }                      // set the y position of the character
        inline void setZ(int z) override { pos.setZ(z); }                      // set the z position of the character
        
        inline const int getX() const override { return pos.getX(); } // get the x position of the character
        inline const int getY() const override { return pos.getY(); } // get the y position of the character
        inline const int getZ() const override { return pos.getZ(); } // get the z position of the character

        void update() override;
        void setGame(Game *game) override
        {
            this->game = game;
        }
        std::vector<CollisionInfo> overlap(Entity *other) override
        {
            std::vector<CollisionInfo> res;
            auto temp = other->allPoints();
            auto cur = allPoints();
            for (const auto &ot : temp)
            {
                for (const auto &th : cur)
                {
                    if (ot == th)
                    {
                        res.push_back(CollisionInfo{std::get<0>(ot), std::get<1>(ot), std::get<2>(ot), this, other});
                    }
                }
            }
            return res;
        }
        std::vector<std::tuple<int, int, int>> allPoints()
        {
            return std::vector<std::tuple<int, int, int>>{{getX(), getY(), getZ()}};
        }
        std::tuple<int, int, int> getPoint()
        {
            return std::tuple<int, int, int>{getX(), getY(), getZ()};
        }
        std::vector<OutofBound> outofbound();
    };
    class Compound : public Entity
    {
    public:
        std::vector<Character*> contents;
        int centerx;        // used for teleportation
        int centery;        // used for teleportation
        int z = 0;          
        std::tuple<int, int, int, int> bound;   // <minx, maxx, miny, maxy>
        Compound(std::tuple<int,int,int,int> bound, Game *game =nullptr):Entity{game}, bound{bound}{}
        Compound(int centerx, int centery, int z, std::tuple<int, int, int, int> bound, Game *game = nullptr) : Entity{game}, centerx{centerx}, centery{centery}, z{z}, bound{bound}
        {
        }
        ~Compound(){
            for(Character* chara: contents){
                delete chara;
            }
        }
        void draw(WINDOW *playground) override
        {
            for (Character* chara : contents)
            {
                chara->draw(playground);
            }
        }
        void update() override;
        
        inline const int getX() const override { return centerx; }
        inline const int getY() const override { return centery; }
        inline const int getZ() const override { return z; }

        inline void setX(int x) override { centerx = x; }
        inline void setY(int y) override { centery = y; }
        inline void setZ(int z) override { this->z = z; }

        void setGame(Game *game) override
        {
            this->game = game;
            for (Character* chara : contents)
            {
                chara->setGame(game);
            }
        }
        std::vector<std::tuple<int, int, int>> allPoints()
        {
            std::vector<std::tuple<int, int, int>> res;
            for (Character* chara : contents)
            {
                res.push_back(chara->getPoint());
            }
            return res;
        }
        std::vector<CollisionInfo> overlap(Entity *other) override
        {
            std::vector<CollisionInfo> res;
            auto temp = other->allPoints();
            auto cur = allPoints();
            for (const auto &ot : temp)
            {
                for (const auto &th : cur)
                {
                    if (ot == th)
                    {
                        res.push_back({std::get<0>(ot), std::get<1>(ot), std::get<2>(ot), this, other});
                    }
                }
            }
            return res;
        }
        std::vector<OutofBound> outofbound();
    };
    class Rectangle : public Compound
    {
        int width;
        int length;

    public:
        Rectangle(int left, int top, int length, int width, char content, int z = 0) : Compound{left + width / 2, top + length / 2, z, std::tuple<int, int, int, int>{left, left + length - 1, top, top + width - 1}}, width{width}, length{length}
        {
            for (int i = left; i < left + length; i++)
            {
                for (int j = top; j < top + width; j++)
                {
                    contents.push_back(new Character{i, j, content});
                }
            }
        }
    };
    class BitMap : public Compound
    {
    public:
        BitMap(std::vector<std::tuple<int, int, char>> content, int z = 0) : Compound{
                                                                                 std::accumulate(content.begin(), content.end(), 0, [](int res, std::tuple<int, int, char> b)
                                                                                                 { return res + std::get<0>(b); }) /
                                                                                     (int)content.size(),
                                                                                 std::accumulate(content.begin(), content.end(), 0, [](int res, std::tuple<int, int, char> b)
                                                                                                 { return res + std::get<1>(b); }) /
                                                                                     (int)content.size(),
                                                                                 z, [](std::vector<std::tuple<int, int, char>> &bm)
                                                                                 {
                                                                                     if (bm.empty())
                                                                                         throw "Empty Object";
                                                                                     else
                                                                                     {
                                                                                         auto [minx, miny, ch] = bm[0];
                                                                                         int maxx = minx;
                                                                                         int maxy = miny;
                                                                                         for (size_t i = 1; i < bm.size(); i++)
                                                                                         {
                                                                                             auto [x, y, c] = bm[i];
                                                                                             if (x > maxx)
                                                                                                 maxx = x;
                                                                                             else if (x < minx)
                                                                                                 minx = x;
                                                                                             if (y > maxy)
                                                                                                 maxy = y;
                                                                                             else if (y < miny)
                                                                                                 miny = y;
                                                                                         }
                                                                                         return std::tuple<int, int, int, int>{minx, maxx, miny, maxy};
                                                                                     }
                                                                                 }(content)}
        {
            for (const auto &[x, y, ch] : content)
            {
                contents.push_back(new Character{x, y, ch});
            }
        }
    };
   
}
#endif