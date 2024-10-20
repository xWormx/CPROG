#include "Component.h"


Component::Component(int x, int y, int w, int h) : rect{ x, y, w, h }
{ 
}

SDL_Rect* Component::getRect()
{
    return &rect;
}

Component::~Component()
{    
}