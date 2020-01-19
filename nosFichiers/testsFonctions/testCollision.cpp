#include "graph/mingl.h"
#include "graph/pos.h"

#include <cassert>

using namespace std;

bool collisions(pos &entity1,
                pos &entity2,
                const unsigned &height1,
                const unsigned &height2,
                const unsigned &width1,
                const unsigned &width2)
{
    if (entity1.getOrd() + height1 >= entity2.getOrd() && entity1.getOrd() <= entity2.getOrd() + height2)
        if (entity1.getAbs() + width1 >= entity2.getAbs() && entity1.getAbs() <= entity2.getAbs() + width2)
            return true;

    return false;
}

void testCollision()
{
    pos a(0, 0), b(10, 10);
    assert(collisions(a, b, 20, 20, 20, 20));

    a = pos(10, 0);
    b = pos(0, 10);
    assert(collisions(a, b, 20, 20, 20, 20));

    a = pos(0, 0);
    b = pos(20, 20);
    assert(collisions(a, b, 20, 20, 20, 20));

    a = pos(0, 10);
    b = pos(10, 0);
    assert(collisions(a, b, 20, 20, 20, 20));

    a = pos(0, 0);
    b = pos(0, 0);
    assert(collisions(a, b, 20, 20, 20, 20));

    a = pos(0, 0);
    b = pos(0, 0);
    assert(collisions(a, b, 5, 15, 30, 20));

    a = pos(10, 0);
    b = pos(0, 13);
    assert(collisions(a, b, 15, 20, 5, 20));

    a = pos(10, 0);
    b = pos(0, 16);
    assert(!collisions(a, b, 15, 20, 5, 20));

    a = pos(10, 0);
    b = pos(16, 0);
    assert(!collisions(a, b, 15, 20, 5, 20));

    a = pos(10, 0);
    b = pos(25, 25);
    assert(!collisions(a, b, 15, 20, 5, 20));

    a = pos(10, 21);
    b = pos(0, 0);
    assert(!collisions(a, b, 15, 20, 5, 20));
}
