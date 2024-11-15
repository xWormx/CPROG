#include "Elephant.h"

Elephant* Elephant::getInstance(std::string n, int w, int t)
{
    return new Elephant(n, w, t);
}

Elephant::Elephant(std::string n, int w, int t1) : Animal(n,w), trunkLength(t1)
{
}

int Elephant::getTrunkLength() const
{
    return trunkLength;
}