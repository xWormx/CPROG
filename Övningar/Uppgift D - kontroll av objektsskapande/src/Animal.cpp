#include "Animal.h"

Animal::Animal(std::string n, int w) : name(n), weight(w){}

Animal::~Animal(){}


std::string Animal::getName() const
{
    return name;
}

int Animal::getWeigth() const
{
    return weight;
}