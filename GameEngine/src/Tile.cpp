#include "Tile.h"

Tile * Tile::getInstance(int x, int y, int w, int h, std::string srcImage)
{
    return new Tile(x, y, w, h, srcImage);
}

void Tile::tick()
{
    Position playerPos = playerRef->GetPosition();
    if ((playerPos.x + (playerRef->GetWidth() / 3)) < 5)
    {
        xPos += 5;
        setPosition(xPos, yPos);
    }
}