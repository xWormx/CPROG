#include "Tile.h"

Tile * Tile::GetInstance(int x, int y, int w, int h, std::string srcImage)
{
    return new Tile(x, y, w, h, srcImage);
}

void Tile::Tick(System& system)
{
    int windowBoundDistance = 5;

    //Move(-1, 0);
    if(Collider2DIsValid())
        SetColliderBounds({GetDestRect().x, GetDestRect().y + GetColliderBounds().h, width, GetColliderBounds().h});
    
    if(playerRef != nullptr)
    {
        /* Player* p = playerRef;
        if (p->GetColliderBounds().x < windowBoundDistance)
        {
            // Kan för flytta med player->GetMoveSpeed();
            Move(5, 0);
        }

        if(p->GetColliderBounds().x + p->GetColliderBounds().w > engine.GetWindowWidth() - windowBoundDistance)
        {
            Move(-5, 0);
        }

        if(p->GetColliderBounds().y < windowBoundDistance)
        {
            Move(0, 5);
        }

        if(p->GetColliderBounds().y + p->GetColliderBounds().h > engine.GetWindowHeight() - windowBoundDistance)
        {
  
            Move(0, -5);
        }
        

 */
    }
}