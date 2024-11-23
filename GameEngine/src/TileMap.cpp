#include "Tilemap.h"

TileMap* TileMap::GetInstance(int x, int y, int tileW, int tileH)
{
    
    return new TileMap(x, y, tileW, tileH);
}

TileMap::TileMap(int x, int y, int tileW, int tileH) : mapPosition{x,y}, tileSize{tileW, tileH} 
{
    LoadTileImageMap("map1.txt");
}

void TileMap::InitializeTiles()
{
    for(int y = 0; y < mapDimension.h; y++)
    {
        for(int x = 0; x < mapDimension.w; x++)
        {
            Tile *t;
            char imageIndex = tileImageIndex[x + (y * mapDimension.w)];
            if(imageIndex <= 0)
                return;

            switch(imageIndex)
            {
                case '0':
                    {
                        int xp = mapPosition.x + (x * tileSize.w);
                        int yp = mapPosition.y + (y * tileSize.h);
                        t = Tile::GetInstance(xp, yp, tileSize.w, tileSize.h, "UIButton.png" ); 
                        t->InstallCollider2D(true,{xp, yp, tileSize.w, tileSize.h}, false, true);
                    } break;
                case '1':    
                    {
                        t = Tile::GetInstance(mapPosition.x + (x * tileSize.w), mapPosition.y + (y * tileSize.h), tileSize.w, tileSize.h, "iconDown.png" ); 
                    } break;
            }
            
            t->SetPlayerReference(playerRef);
            appRef->AddSprite(t);

        }
    }
}

void TileMap::LoadTileImageMap(std::string srcFile)
{
    std::string fullPath = constants::gResPath + "TileMapData/" + srcFile;
    std::ifstream f(fullPath);
    if(!f.is_open())
    {
        std::cout << "couldn't open file" << fullPath << std::endl;
    }
    else
    {
        bool withCalculated = false;
        int w = 0;
        int h = 0;
        char c;
        while(f.get(c))
        {
            if(c == '\n')
            {
                h++;
                withCalculated = true;
            }
            else if(!withCalculated)    
                w++;
            
            if(c != '\n')
                tileImageIndex.push_back(c);
            std::cout << c;
        }

        h++; // to register last line because we reached eof instaed of '\n'
        
        mapDimension.w = w;
        mapDimension.h = h;

        std::cout << "\nwidth = " << w << "| h = " << h << std::endl;
    }
}

TileMap::~TileMap()
{

}
