#include "../AGE/entity.h"
using namespace GameEngine;
class Ghost : public Character{
        bool frightened;
        bool alive;
    public:
        void kill(); // kill the ghost
        void setfrighten(bool);
        bool is_frightened() const;
        void update() override;
}