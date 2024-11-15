#ifndef TILE_H
#define TILE_H

#include "System.h"
#include "MovableSprite.h"
#include "Player.h"

class Tile : public MovableSprite
{
    public:
        static Tile* getInstance(int x, int y, int w, int h, std::string srcImage);
        void tick(System& system);

        void SetPlayerReference(Player* p)
        {
            playerRef = p;
        }


    protected:
        Tile(int x, int y, int w, int h, std::string srcImage) : MovableSprite(x, y, w, h, srcImage), xPos(x), yPos(y), width(w), height(h) {}
    private:
        int xPos, yPos, width, height;
        Player* playerRef = nullptr;
};

#endif