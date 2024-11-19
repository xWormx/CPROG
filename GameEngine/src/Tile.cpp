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
        if ((p->GetPosition().x + (p->GetSize().w / 3)) < 5)
        {
            xPos += 5;
            setPosition(xPos, yPos);
        }

        if(p->GetPosition().x + (p->GetSize().w - p->GetSize().w/3) > engine.GetWindowWidth() - 5)
        {
            xPos -= 5;
            setPosition(xPos, yPos);
        }

        if(p->GetPosition().y + 60 < 0)
        {
            yPos += 5;
            setPosition(xPos, yPos);
        }

        if(p->GetPosition().y + p->GetSize().h > engine.GetWindowHeight() - 10)
        {
            
            yPos -= 5;
            setPosition(xPos, yPos);
        }

    }
}