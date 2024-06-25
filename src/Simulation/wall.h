#pragma once
#include "../Math/vector.h"

class Wall{
private:
    Vector<2> anchor;
    Vector<2> direction;

public:
    explicit Wall(Vector<2> _anchor, Vector<2> _direction) :
        anchor(_anchor), direction(_direction)
    {}

    friend class Particle;
};
