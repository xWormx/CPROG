#include "System.h"
#include "Label.h"
#include "Button.h"
#include "StaticSprite.h"
#include "MovableSprite.h"
#include "TextButton.h"

#define FPS 60


struct Position
{
    int x, y;
};



class Player : public MovableSprite
{
    public: 
        static Player* getInstance(int x, int y, int h, int w, std::string srcImage)
        {
            return new Player(x, y, w, h, srcImage);
        }

        void tick()
        {
            isMoving = false;
            static int tick = 0;
            static int frame = 0;
            
            if(tick % 7 == 0)
            {
                frame ++;
                if(frame > 3) frame = 0;
                int size = 124;
                setSpriteRegion(size * frame, 0, size, size);
            } 

            tick++;

                
            if(keyPressed('d') || InputComponent::getMousePressed(SDL_BUTTON_LEFT))
            {
                pos.x += moveSpeed;
                isMoving = true;
            }
            if(keyPressed('a'))
            {
                pos.x -= moveSpeed;
                isMoving = true;
            }
            if(keyPressed('w'))
            {
                pos.y-= moveSpeed;
                isMoving = true;
            }
            if(keyPressed('s'))
            {
                pos.y += moveSpeed;
                isMoving = true;
            }

            if((pos.x + (width/3)) < 0)
                pos.x = -(width/3);

                
            MovableSprite::setPosition(pos.x, pos.y);
        }

        void setMoveSpeed(int speed)
        {
            moveSpeed = speed;

        }
        bool keyPressed(const int keyCode)
        {
            return InputComponent::getKeyPressed(keyCode);
        }

        int getMoveSpeed() { return moveSpeed; }
        bool IsMoving() {return isMoving;}
        const Position& GetPosition() { return pos; }
        const int& GetWidth() { return width; }
        void SetPlayerRef(Player* p)
        {
            playerRef = p;
        }
        
    protected:
        Player(int x, int y, int h, int w, std::string srcImage) : MovableSprite(x,y,w,h,srcImage), pos{x, y}
        {
            width = w;
            height = h;
        }

    private:
        Position pos;
        int width;
        int height;
        int moveSpeed = 0;
        bool isMoving;
        TextButton* text;
        Player* playerRef = nullptr;
};



class Tile : public MovableSprite
{
    public:
        static Tile* getInstance(int x, int y, int w, int h, std::string srcImage)
        {
            return new Tile(x,y,w,h,srcImage);
        }

        void SetPlayerReference(Player* p)
        {
            playerRef = p;
        }

        void tick()
        {
            Position playerPos = playerRef->GetPosition();
            if((playerPos.x + (playerRef->GetWidth() / 3)) < 5)
            {
                xPos+=5;
                setPosition(xPos, yPos);
            }    
        }

    protected:
        Tile(int x, int y, int w, int h, std::string srcImage) : MovableSprite(x, y, w, h, srcImage), xPos(x), yPos(y), width(w), height(h)
        {
        }
    private:
        int xPos, yPos, width, height;
        Player* playerRef;
};


class UIElement : public TextButton
{
    public:
        static UIElement* getInstance(int x, int y, int w, int h, std::string txt, std::string srcImage)
        {
            return new UIElement(x, y, w, h, txt, srcImage);
        }
        void tick()
        {
            if(InputComponent::getKeyPressed('w'))
            {
                setText("KICK");
            }
            else
            {
                setText("HOLLIMOLLLIII");
            }
        }

    protected:
        UIElement(int x, int y, int w, int h, std::string txt, std::string srcImage) : TextButton(x, y, w, h, txt, srcImage)
        {
        }
    
    private:
        int s;
};

int main(int argv, char **argc)
{
    System app(FPS, {255, 150, 70, 255});
    
    int buttonW = 150, buttonH = 100;
    UIElement* uiButton = UIElement::getInstance(engine.GetWindowWidth() / 2 - (buttonW * 2), engine.GetWindowHeight() / 2, 
                                                    buttonW, buttonH, 
                                                    "HEJ", "UIButton.png");


    Player* player1 = Player::getInstance(200, 200, 300, 300, "PersonIdle.png");
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