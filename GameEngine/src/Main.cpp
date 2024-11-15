
#include "System.h"
#include "StaticSprite.h"
#include "MovableSprite.h"
#include "TextButton.h"
#include "Player.h"
#include "Enemy.h"
#include "UIElement.h"
#include "Tile.h"
#include "TileMap.h"
#include "TextFragment.h"

#define FPS 60

int main(int argv, char **argc)
{
    
    System app(FPS, {255, 150, 70, 255});
    
    int buttonW = 150, buttonH = 30;
    UIElement* uiButton = UIElement::getInstance(engine.GetWindowWidth() / 2 - (buttonW * 2), engine.GetWindowHeight() / 2, 
                                                    buttonW, buttonH, 
                                                    "HEJ", "UIButton.png");


    Player* player1 = Player::getInstance(200, 200, 300, 300, "PersonIdle.png", 20);
    player1->SetUIElementRef(uiButton);
    player1->SetAppRef(&app);  
    player1->setSpriteRegion(0, 0, 124, 124);
    player1->setMoveSpeed(5);
    player1->SetSpriteCollection(app.GetSpriteCollection());

    Enemy* enemy = Enemy::getInstance(200, 200, 300, 300, "PersonIdle.png", 20);

    TileMap* map1 = TileMap::getInstance(-50, 0, 60, 60);
    map1->SetAppRef(&app);
    map1->SetPlayerRef(player1);
    map1->InitializeTiles();

    TextFragment* t = TextFragment::getInstance(0, 0, 200, 80, "YOOOO", {0xff,0,0xbb,0xff});
   
    app.addSprite(t);
    app.addSprite(player1);
    app.addSprite(enemy);
    app.addSprite(uiButton);
    
    app.run();

 
    return 0;
}