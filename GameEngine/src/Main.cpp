
#include "System.h"
#include "StaticSprite.h"
#include "MovableSprite.h"
#include "Player.h"
#include "Enemy.h"
#include "Tile.h"
#include "TileMap.h"
#include "TextFragment.h"
#include "Button.h"
#include "TextButton.h"
#include "TextField.h"

#define FPS 60

int main(int argv, char **argc)
{
    System app(FPS, {255, 150, 70, 255});

    int w = 100, h = 30;
    TextFragment* t = TextFragment::GetInstance(100, 100, w, h, "Test", {0xff,0,0xbb,0xff});
    Button* b = Button::GetInstance(100, 100, w, h, "UIButton.png");

    // TextFragment och Button läggs inte till i app.AddSprite()
    // men det gör TextButton. Däremot så när TextButtons tick() funktion körs så är det enda
    // den gör att köra text->tick() och button->tick().....
    // men behövder den det????
    // den kan ju bara uppdatera båda objekten i sin egen tick egentligen?
    // däremot kanske det kan vara bra att köra deras respektive tick() om de
    // har något internt beteende som borde hända där???
    TextButton* textButton = TextButton::GetInstance(t, b);

    Player* player1 = Player::GetInstance(100, 200, 64, 100, "PersonIdle_Small.png", 20);
    app.AddCollider(player1);
    player1->SetCollider(true, {200, 200, 64, 100});
    player1->SetTextButtonRef(textButton);
    player1->setSpriteRegion(0, 0, 124, 124);
    player1->SetMoveSpeed(5);
    player1->SetTag("player");

    Enemy* enemy = Enemy::GetInstance(600, 200, 150, 150, "PersonIdle.png", 20);
    app.AddCollider(enemy);
    enemy->SetCollider(true, {200, 200, 300, 300});
    enemy->SetTag("enemySmall");

    TileMap* map1 = TileMap::GetInstance(-50, 0, 60, 60);
    map1->SetAppRef(&app);
    map1->SetPlayerRef(player1);
    map1->InitializeTiles();

    TextField* textField = TextField::GetInstance(200, 200, {0xff, 0xff, 0xff, 0xff});
    TextField* nameField = TextField::GetInstance(200, 250, {0xff, 0xff, 0xff, 0xff});

    app.AddSprite(textField);
    app.AddSprite(nameField);
    app.AddSprite(textButton);
    app.AddSprite(player1);
    app.AddSprite(enemy);

    app.Run();

 
    return 0;
}