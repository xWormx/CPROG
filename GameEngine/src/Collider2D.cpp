#include "Collider2D.h"

Collider2D::Collider2D(const bool& colliderState, const SDL_Rect& bounds, const bool& _isTrigger, const bool& _isStatic) : 
canCollide(colliderState), isTrigger(_isTrigger), isStatic(_isStatic), rect(bounds) 
{
}