#include "Elephant.h"

Elephant::Elephant(std::string n, int w, int t1) : Animal(n,w), trunk(t1)
{

}

int Elephant::getTrunkLength() const
{
    return trunkLength;
}