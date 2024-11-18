
#include "System.h"
#include "StaticSprite.h"
#include "MovableSprite.h"
#include "Player.h"
#include "Enemy.h"
//#include "UIElement.h"
#include "Tile.h"
#include "TileMap.h"
#include "TextFragment.h"
#include "Button.h"
#include "TextButton.h"

#define FPS 60

int main(int argv, char **argc)
{
    
    System app(FPS, {255, 150, 70, 255});

    int w = 100, h = 30;
    TextFragment* t = TextFragment::getInstance(100, 100, w, h, "YOOOO", {0xff,0,0xbb,0xff});
    Button* b = Button::getInstance(100, 100, w, h, "UIButton.png");

    TextButton* textButton = TextButton::getInstance(t, b);

    Player* player1 = Player::getInstance(100, 200, 64, 100, "PersonIdle_Small.png", 20);
    app.addCollider(player1);
    player1->SetCollider(true, {200, 200, 64, 100});
    player1->SetTextButtonRef(textButton);
    player1->setSpriteRegion(0, 0, 124, 124);
    player1->setMoveSpeed(5);

    Enemy* enemy = Enemy::getInstance(600, 200, 150, 150, "PersonIdle.png", 20);
    app.addCollider(enemy);
    enemy->SetCollider(true, {200, 200, 300, 300});

    TileMap* map1 = TileMap::getInstance(-50, 0, 60, 60);
    map1->SetAppRef(&app);
    map1->SetPlayerRef(player1);
    map1->InitializeTiles();

    app.addSprite(t);
    app.addSprite(b);
    app.addSprite(player1);
    app.addSprite(enemy);
    app.addSprite(textButton);

    app.run();

 
    return 0;
}