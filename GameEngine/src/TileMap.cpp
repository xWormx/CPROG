#include "Tilemap.h"

TileMap* TileMap::GetInstance(int x, int y, int tileW, int tileH)
{
    
    return new TileMap(x, y, tileW, tileH);
}

TileMap::TileMap(int x, int y, int tileW, int tileH) : mapPosition{x,y}, tileSize{tileW, tileH} 
{
    LoadTileImageMap("map1.txt");
}

void TileMap::InitializeTiles(const System& system)
{
    for(int y = 0; y < mapDimension.h; y++)
    {
        for(int x = 0; x < mapDimension.w; x++)
        {
            Tile *t;
            char imageIndex = tileImageIndex[x + (y * mapDimension.w)];
            if(imageIndex <= 0)
                return;


            int xp = mapPosition.x + (x * tileSize.w);
            int yp = mapPosition.y + (y * tileSize.h);
            switch(imageIndex)
            {
                case '0':
                    {
                        //t = Tile::GetInstance(xp, yp, tileSize.w, tileSize.h, "UIButton.png" ); 
                        //t->InstallCollider2D(true,{xp, yp, tileSize.w, tileSize.h}, false, true);

                        t = Tile::GetInstance(xp, mapPosition.y + ((y-1) * tileSize.h), tileSize.w, tileSize.h * 2, "ground1.png" ); 
                        //int regionX = engine.GetRandomNumberInRange(0, 1);
                        t->InstallCollider2D(true,{xp, yp, tileSize.w, tileSize.h}, false, true);
                        t->setSpriteRegion(0, 64 * 1, 64, 64 * 2);
                        t->SetLayerTag("foreGround");
                    } break;
                case '1':    
                    {
                        t = Tile::GetInstance(mapPosition.x + (x * tileSize.w), mapPosition.y + (y * tileSize.h), tileSize.w, tileSize.h, "ground1.png" ); 
                        int regionX = engine.GetRandomNumberInRange(0, 1);
                        t->setSpriteRegion(regionX * 64, 0, 64, 64);
                        t->SetLayerTag("ground");
                    } break;
                case 'b':
                    {   

                    } break;
            }
            
            t->SetTag("tile");
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
