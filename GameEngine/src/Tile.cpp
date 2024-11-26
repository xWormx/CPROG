#include "Tile.h"

Tile * Tile::GetInstance(int x, int y, int w, int h, std::string srcImage)
{
    return new Tile(x, y, w, h, srcImage);
}

void Tile::Tick(System& system)
{

    int targetValue = tileMap->GetSize().w - 1;
    auto it = std::find_if(tileMap->GetTiles().begin(), tileMap->GetTiles().end(), [targetValue](Tile* t)
    {
        return t->mapIndex == targetValue;
    });

    Tile* topRightTile = nullptr;
    if(it != tileMap->GetTiles().end())
    {   
        topRightTile = *it;
    }


    targetValue = ((tileMap->GetSize().w) * (tileMap->GetSize().h - 1)) - 1;
    it = std::find_if(tileMap->GetTiles().begin(), tileMap->GetTiles().end(), [targetValue](Tile* t)
    {
        return t->mapIndex == targetValue;
    });

    Tile* bottomLeftTile = nullptr;
    if(it != tileMap->GetTiles().end())
    {   
        bottomLeftTile = *it;
    }


    if(topRightTile->GetDestRect().x + topRightTile->GetDestRect().w >= engine.GetWindowWidth())
        Move(-1, 0);
    
    if(Collider2DIsValid())
        SetColliderBounds({GetDestRect().x, GetDestRect().y + GetColliderBounds().h, width, GetColliderBounds().h});
    
    int windowBoundDistance = 100;
    if(playerRef != nullptr)
    {
        Player* p = playerRef;
        
        
        if(p->GetColliderBounds().y < windowBoundDistance)
        {
            if(topRightTile->GetDestRect().y <= 0)
                Move(0, 5);
        }

        if((p->GetColliderBounds().y + p->GetColliderBounds().h) > (engine.GetWindowHeight() - windowBoundDistance))
        {
            if(bottomLeftTile->GetDestRect().y + bottomLeftTile->GetDestRect().h >= engine.GetWindowHeight())
                Move(0, -5);
        }
        

 
    }
}