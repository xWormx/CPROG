#include "Tile.h"

Tile * Tile::GetInstance(int x, int y, int w, int h, std::string srcImage)
{
    return new Tile(x, y, w, h, srcImage);
}

void Tile::Tick(System& system)
{
    if(playerRef != nullptr)
    {
        Player* p = playerRef;
        if (p->GetColliderBounds().x < 30)
        {
            // Kan för flytta med player->GetMoveSpeed();
            Move(5, 0);
        }

        if(p->GetColliderBounds().x + p->GetColliderBounds().w > engine.GetWindowWidth() - 30)
        {
            Move(-5, 0);
        }

        if(p->GetColliderBounds().y < 30)
        {
            Move(0, 5);
        }

        if(p->GetColliderBounds().y + p->GetColliderBounds().h > engine.GetWindowHeight() - 30)
        {
  
            Move(0, -5);
        }
        if(Collider2DIsValid())
            SetColliderBounds({GetDestRect().x, GetDestRect().y + GetColliderBounds().h, width, GetColliderBounds().h});

    }
}