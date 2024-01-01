#include <utility>
#include <vector>
#include <algorithm>
namespace GameEngine
{
    enum class Border
    {
        Left,
        Right,
        Top,
        Down
    };
    class Entity;
    class Compound;
    class Character;
    class Movement
    {
    public:
        virtual void transform(Character &) = 0;
        virtual void transform(Compound &) = 0;
    };
    class Simple : public Movement
    {
    public:
        virtual void transform(Character &) = 0;
        virtual void transform(Compound &) = 0;
    };

    class Move : public Simple
    {
        std::pair<int, int> dir;

    public:
        Move(int dx, int dy) : dir{dx, dy} {}
        Move(Border border)
        {
            switch (border)
            {
            case Border::Top:
                dir.first = 0;
                dir.second = -1;
                break;
            case Border::Left:
                dir.first = -1;
                dir.second = 0;
                break;
            case Border::Down:
                dir.first = 0;
                dir.second = 1;
                break;
            case Border::Right:
                dir.first = 1;
                dir.second = 0;
                break;
            }
        }
        void transform(Character &chara) override;
        void transform(Compound &comp) override;
    };

    class Scale : public Simple
    {
        int amp;

    public:
        Scale(int amp) : amp{amp} {}
        void transform(Character &chara) override;
        void transform(Compound &comp) override;
    };
    // Teleport to a given location
    class Teleport : public Simple
    {
        int x, y;

    public:
        Teleport(int x, int y) : x{x}, y{y} {}
        void transform(Character &chara) override;
        void transform(Compound &comp) override;
    };

    // A complex move consists of a sequence of simple moves
    class Complex : public Movement
    {
    protected:
        int i = 0;                   // current frame
        std::vector<Simple *> moves; // a sequence of simple moves

    public:
        Complex() {}
        Complex(std::vector<Simple *> moves) : moves{moves} {}
        void transform(Character &entity) override;
        void transform(Compound &comp) override;
    };

    class Straight : public Complex
    {
        // follows the vector (x,y)
        std::vector<std::pair<int, int>> Bresenham(int x0, int y0, int x1, int y1)
        {
            std::vector<std::pair<int, int>> points;
            bool steep = abs(y1 - y0) > abs(x1 - x0);
            if (steep)
            {
                std::swap(x0, y0);
                std::swap(x1, y1);
            }
            if (x0 > x1)
            {
                std::swap(x0, x1);
                std::swap(y0, y1);
            }

            int deltax = x1 - x0;
            int deltay = abs(y1 - y0);
            int error = deltax / 2;
            int ystep = y0 < y1 ? 1 : -1;
            int y = y0;
            for (int x = x0; x <= x1; x++)
            {
                if (steep)
                    points.push_back({y, x});
                else
                    points.push_back({x, y});
                error = error - deltay;
                if (error < 0)
                {
                    y = y + ystep;
                    error = error + deltax;
                }
            }
            return points;
        }

    public:
        Straight(int x, int y)
        {
            std::vector<std::pair<int, int>> points = Bresenham(0, 0, x, y);
            // when y < 0, the points are in reverse order
            if (y < 0)
                std::reverse(points.begin(), points.end());
            for (size_t i = 0; i < points.size() - 1; i++)
            {
                moves.push_back(new Move{points[i + 1].first - points[i].first, points[i + 1].second - points[i].second});
            }
        }
    };

    class Gravitating : public Move
    {
    public:
        Gravitating(Border border) : Move{border} {}
    };

}