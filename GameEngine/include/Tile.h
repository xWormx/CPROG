#ifndef TILE_H
#define TILE_H

#include "System.h"
#include "MovableSprite.h"
#include "Player.h"
#include "TileMap.h"
#include "Dimension.h"
#include <algorithm>


class TileMap;

class Tile : public MovableSprite
{
    public:
        static Tile* GetInstance(int x, int y, int w, int h, std::string srcImage);
        void Tick(System& system);
        void SetMapIndex(int i) { mapIndex = i; }
        void SetmapSize(Dimension size) { mapSize = size; }
        void SetMapRef(TileMap* map) { tileMap = map; }
        void SetPlayerReference(Player* p)
        {
            playerRef = p;
        }


    protected:
        Tile(int x, int y, int w, int h, std::string srcImage) : MovableSprite(x, y, w, h, srcImage), xPos(x), yPos(y), width(w), height(h) {}
    private:
        int xPos, yPos, width, height;
        int mapIndex;
        Dimension mapSize;
        TileMap* tileMap;
        Player* playerRef = nullptr;
};

#endif