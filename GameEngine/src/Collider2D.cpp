#include "Collider2D.h"

Collider2D::Collider2D(const bool& colliderState, const SDL_Rect& bounds)
{
    canCollide = colliderState;
    rect = bounds;
}