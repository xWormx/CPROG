#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"
#include "Position.h"
#include "Dimension.h"
#include <fstream>
class TileMap
{
    public:
        static TileMap* GetInstance(int x, int y, int tileW, int tileH);
        void SetAppRef(System* app) { appRef = app;}
        void SetPlayerRef(Player* player) { playerRef = player;}
        void LoadTileImageMap(std::string srcFile);
        void InitializeTiles();
        void Tick(System& system);
        void draw();
        ~TileMap();

    protected:
        TileMap(int x, int y, int tileW, int tileH);
    
    private:
        Position mapPosition;
        Dimension mapDimension;
        Dimension tileSize;
        std::vector<unsigned char> tileImageIndex;
        System* appRef = nullptr;
        Player* playerRef = nullptr;

};


#endif