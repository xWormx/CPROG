#include "System.h"




#include "Label.h"
#include "Button.h"
#include "StaticSprite.h"
#include "MovableSprite.h"
#include "TextButton.h"
#include "Player.h"
#include "UIElement.h"
#include "Tile.h"

int main(int argv, char **argc)
{
    #define FPS 60
    System app(FPS, {255, 150, 70, 255});
    
    int buttonW = 150, buttonH = 100;
    UIElement* uiButton = UIElement::getInstance(engine.GetWindowWidth() / 2 - (buttonW * 2), engine.GetWindowHeight() / 2, 
                                                    buttonW, buttonH, 
                                                    "HEJ", "UIButton.png");


    Player* player1 = Player::getInstance(200, 200, 300, 300, "PersonIdle.png");
    player1->SetUIElementRef(uiButton);
    player1->SetAppRef(&app);
    Player* player2 = Player::getInstance(200, 200, 300, 300, "PersonIdle.png");
    player1->setSpriteRegion(0, 0, 124, 124);
    player1->setMoveSpeed(5);
    
    const int mapW = 10;
    const int mapH = 10;
    const int tileW = 24;
    const int tileH = 24;

    Tile* tileMap[mapW * mapH];
    for(int y = 0; y < mapH; y++ )
    {
        for(int x = 0; x < mapW; x++)
        {
            Tile* tile = tileMap[x + (y * mapW)];
            if(x % 2 == 0)
                tile = Tile::getInstance(x*(tileW), y * (tileH), tileW, tileH, "iconDown.png");
            else
                tile = Tile::getInstance(x*(tileW), y * (tileH), tileW, tileH, "iconUp.png");
            tile->setSpriteRegion(0, 0, 32, 32);
            tile->SetPlayerReference(player1);
            app.addSprite(tile);
        }
    }


    app.addSprite(player1);
    app.addSprite(player2);
    app.addSprite(uiButton);

    
    app.run();

 
    return 0;
}