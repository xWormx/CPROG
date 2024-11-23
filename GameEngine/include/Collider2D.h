#ifndef COLLIDER2D_H
#define COLLIDER2D_H

#include "SDL2\SDL.h"


struct Collider2D
{
    public:
        Collider2D(const bool& colliderState, const SDL_Rect& bounds, const bool& _isTrigger, const bool& _isStatic);
        void SetBounds(const SDL_Rect& bounds) { rect = bounds; } 
        void SetCollideState(const bool& collideState) { canCollide = collideState;}

        const SDL_Rect& GetBounds() const { return rect; }
        const bool& IsTrigger() const { return isTrigger; }
        const bool& IsStatic() const { return isStatic; }

    private:
        bool canCollide;
        bool isTrigger, isStatic;
        SDL_Rect rect;


};


#endif