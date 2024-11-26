
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
    Level* level1 = Level::GetInstance(1); 
    app.AddLevel(level1);
    Level* level2 = Level::GetInstance(2); 
    app.AddLevel(level2);
    
    int w = 100, h = 30;
    TextFragment* t = TextFragment::GetInstance(100, 100, w, h, "Test", {0xff,0,0xbb,0xff});
    t->SetTag("TextFragmen");
    Button* b = Button::GetInstance(100, 100, w, h, "UIButton.png");
    b->SetTag("Button");
    // TextFragment och Button läggs inte till i app.AddSprite()
    // men det gör TextButton. Däremot så när TextButtons tick() funktion körs så är det enda
    // den gör att köra text->tick() och button->tick().....
    // men behövder den det????
    // den kan ju bara uppdatera båda objekten i sin egen tick egentligen?
    // däremot kanske det kan vara bra att köra deras respektive tick() om de
    // har något internt beteende som borde hända där???
    TextButton* textButton = TextButton::GetInstance(t, b);
    textButton->SetTag("textButton");

   //throw std::runtime_error("FIXA COLLISION RESOLVE");
    Player* player1 = Player::GetInstance(100, 200, 64, 100, "PersonIdle_Small.png", 20);
    player1->InstallCollider2D(true, {200, 200, 64, 100}, false, false);
    player1->SetTextButtonRef(textButton);
    player1->setSpriteRegion(0, 0, 124, 124);
    player1->SetMoveSpeed(5);
    player1->SetTag("player");
    player1->SetLayerTag("foreGround");

    Enemy* enemy = Enemy::GetInstance(600, 200, 64, 100, "PersonIdle_Small.png", 20);
    enemy->InstallCollider2D(true, {200, 200, 300, 300}, false, false);
    player1->setSpriteRegion(0, 0, 124, 124);
    enemy->SetMoveSpeed(2);
    enemy->SetTag("enemySmall");
    enemy->SetLayerTag("foreGround");
    
    // Ska TextField ta emot Sprite för att rama in textfältet? eller
    // hur ska det lösas med inramningen?
    TextField* textField = TextField::GetInstance(200, 200, {0xff, 0xff, 0xff, 0xff});
    textField->SetTag("textField");
    
    
    TextField* nameField = TextField::GetInstance(200, 250, {0xff, 0xff, 0xff, 0xff});
    nameField->SetTag("nameField");

    TileMap* map1 = TileMap::GetInstance(-50, 0, 64, 64);
    map1->SetAppRef(&app);
    map1->SetPlayerRef(player1);
    map1->InitializeTiles(app);
    
    //level1->AddSpriteList({player1, textField, nameField, textButton, enemy});
    level1->AddSpriteList({player1, textButton, enemy});
    level2->AddSprite(player1);
 
    app.Run();

    return 0;
}