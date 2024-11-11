#include "System.h"
#include "Label.h"
#include "Button.h"
#include "StaticSprite.h"
#include "MovableSprite.h"
#define FPS 60

class Player : public MovableSprite
{
    public: 
        static Player* getInstance(int x, int y, int h, int w, std::string srcImage)
        {
            return new Player(x, y, w, h, srcImage);
        }

        void tick()
        {
            
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

                
                xPos += moveSpeed;
            }
            if(keyPressed('a'))
            {
                xPos -= moveSpeed;

            }
            if(keyPressed('w'))
            {
                yPos -= moveSpeed;
            }
            if(keyPressed('s'))
            {
                yPos += moveSpeed;
            }

            
            MovableSprite::setPosition(xPos, yPos);
        }

        void setMoveSpeed(int speed)
        {
            moveSpeed = speed;

        }
        bool keyPressed(const int keyCode)
        {
            return InputComponent::getKeyPressed(keyCode);
        }

    protected:
        Player(int x, int y, int h, int w, std::string srcImage) : MovableSprite(x,y,w,h,srcImage)
        {
            xPos = x;
            yPos = y;
            width = w;
            height = h;
        }

    private:
        int xPos, yPos;
        int width;
        int height;
        int moveSpeed = 0;
};



class UIElement : public StaticSprite
{
    public:
        static UIElement* getInstance(int x, int y, int w, int h, std::string srcImage)
        {
            return new UIElement(x, y, w, h, srcImage);
        }
        void tick()
        {
            if(InputComponent::getKeyPressed('w'))
            {
            }
        }
    protected:
        UIElement(int x, int y, int w, int h, std::string srcImage) : StaticSprite(x,y,w,h,srcImage){}
    
    private:
        int s;


};

int main(int argv, char **argc)
{
    System app(FPS, {255, 150, 70, 255});
    /*
    int txtHeight = 16;
    Label* lbl = Label::getInstance(0, 0, 32, txtHeight, "HEJ");
    Label* lbl2 = Label::getInstance(50, 50, 300, txtHeight, "MY WORLD IS THE GREATEST EVER!!");
    Button* b1 = Button::getInstance(200, 150, 100, 100, "b1");
    */
    
    int buttonW = 150, buttonH = 100;
    UIElement* uiButton = UIElement::getInstance(engine.GetWindowWidth() / 2 - (buttonW * 2), engine.GetWindowHeight() / 2, buttonW, buttonH,"UIButton.png");
    Player* player1 = Player::getInstance(200, 200, 300, 300, "PersonIdle.png");
    player1->setSpriteRegion(0, 0, 124, 124);
    player1->setMoveSpeed(5);
    
    const int mapW = 10;
    const int mapH = 10;
    const int tileW = 24;
    const int tileH = 24;
    Player* tileMap[mapW * mapH];
    for(int y = 0; y < mapH; y++ )
    {
        for(int x = 0; x < mapW; x++)
        {
            Player* tile = tileMap[x + (y * mapW)];
            if(x % 2 == 0)
                tile = Player::getInstance(x*(tileW), y * (tileH), tileW, tileH, "iconDown.png");
            else
                tile = Player::getInstance(x*(tileW), y * (tileH), tileW, tileH, "iconUp.png");
            tile->setSpriteRegion(0, 0, 32, 32);
            tile->setMoveSpeed(-1);
            app.addSprite(tile);
        }
    }

    //app.add(lbl);
    //app.add(lbl2);
    //app.add(b1);
    app.addSprite(player1);
    app.addSprite(uiButton);
    
    app.run();

 
    return 0;
}