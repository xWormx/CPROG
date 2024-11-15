#include "Tile.h"

Tile * Tile::getInstance(int x, int y, int w, int h, std::string srcImage)
{
    return new Tile(x, y, w, h, srcImage);
}

void Tile::tick(System& system)
{
    if(playerRef != nullptr)
    {
        Player* p = playerRef;
        if ((p->GetPosition().x + (p->GetWidth() / 3)) < 5)
        {
            xPos += 5;
            setPosition(xPos, yPos);
        }

        if(p->GetPosition().x + (p->GetWidth() - p->GetWidth()/3) > engine.GetWindowWidth() - 5)
        {
            xPos -= 5;
            setPosition(xPos, yPos);
        }

        if(p->GetPosition().y + 60 < 0)
        {
            yPos += 5;
            setPosition(xPos, yPos);
        }

        if(p->GetPosition().y + p->GetHeight() > engine.GetWindowHeight() - 10)
        {
            
            yPos -= 5;
            setPosition(xPos, yPos);
        }

    }
}