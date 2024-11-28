
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

class StartGameButton : public Button
{
    public:
        StartGameButton(int x, int y, int w, int h, std::string srcImage) : Button(x,y,w,h,srcImage){}
        void OnMouseHover(System& system)
        {

            int mx = system.GetMousePosition().x;
            int my = system.GetMousePosition().y;

            if(mx > GetDestRect().x && mx < GetDestRect().x+GetDestRect().w &&
                my > GetDestRect().y && my < GetDestRect().y+GetDestRect().h)
            {
                setSpriteRegion(800, 0, 800, 600);
                mouseHover = true;
            }
            else
            {
                setSpriteRegion(0, 0, 800, 600);
                mouseHover = false;
            }
            
        }

        void OnMousePress(System& system)
        {
            if(mouseHover)
            {
                if(system.GetMousePressed(SDL_BUTTON_LEFT))
                {
                    wasPressed = true;
                    setSpriteRegion(800*2, 0, 800, 600);
                    
                }
                else
                {
                    if(wasPressed)
                    {
                        wasPressed = false;
                        system.LoadLevel(1);
                    }
                        
                }
            }
        }

        void OnMouseRelease(System& system)
        {
        }
        
    private:
        bool mouseHover, wasPressed = false;
        

};

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

    Enemy* enemy = Enemy::GetInstance(1200, 200, 200, 200, "EnemySheet.png", 20);
    enemy->InstallCollider2D(true, {200, 200, 300, 300}, false, false);
    enemy->setSpriteRegion(0, 0, 124, 124);
    enemy->SetMoveSpeed(2);
    enemy->SetTag("enemySmall");
    enemy->SetLayerTag("foreGround");
    enemy->SetPlayerRef(player1);


    Enemy* enemy2 = Enemy::GetInstance(1400, 400, 200, 200, "EnemySheet.png", 20);
    enemy2->InstallCollider2D(true, {200, 200, 300, 300}, false, false);
    enemy2->setSpriteRegion(0, 0, 124, 124);
    enemy2->SetMoveSpeed(2);
    enemy2->SetTag("enemySmall");
    enemy2->SetLayerTag("foreGround");
    enemy2->SetPlayerRef(player1);
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
    level1->AddSpriteList({player1, textButton, enemy, enemy2});

    StaticSprite* mainMenuBackground = StaticSprite::GetInstance(0, 0, engine.GetWindowWidth(), engine.GetWindowHeight(), "MainmenuBackground.png"); 
    level2->AddSprite(mainMenuBackground);

    Button* startGameButton = new StartGameButton((engine.GetWindowWidth()/2) - 100, (engine.GetWindowHeight() / 2), 200, 100, "StartGameButton.png");
    level2->AddSpriteList({startGameButton, nameField});
    app.LoadLevel(level2->GetLevelIndex());
    
    app.Run();

    return 0;
}