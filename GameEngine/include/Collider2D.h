#ifndef COLLIDER2D_H
#define COLLIDER2D_H

#include "SDL2\SDL.h"


struct Collider2D
{
    public:

        void SetBounds(const SDL_Rect& bounds) {rect = bounds;} 
        void SetCollideState(const bool& collideState) { canCollide = collideState;}

        const SDL_Rect& GetBounds() const { return rect; }

    private:
        bool canCollide;
        SDL_Rect rect;


};


#endif