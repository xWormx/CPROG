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

        void setSpriteDrawArea(int x, int y, int w, int h)
        {
            setSrcRect(x, y, w, h);
        }

        void tick()
        {
            if(keyPressed('d'))
            {
                xPos++;
            }
            if(keyPressed('a'))
            {
                xPos--;
            }
            if(keyPressed('w'))
            {
                yPos--;
            }
            if(keyPressed('s'))
            {
                yPos++;
            }

            static int tick = 0;
            static int frame = 0;
            
            if(tick % 7 == 0)
            {
                frame ++;
                if(frame > 3) frame = 0;
                setSpriteDrawArea(124 * frame, 0, 124, 124);
            } 

            tick++;

            
            MovableSprite::setPosition(xPos, yPos);
        }

        bool keyPressed(const int keyCode)
        {
            return InputComponent::getKeyCodePressed(keyCode);
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
};

int main(int argv, char **argc)
{
    
    System app(FPS, {255, 150, 70, 255});
    
    int txtHeight = 16;
    Label* lbl = Label::getInstance(0, 0, 32, txtHeight, "HEJ");
    Label* lbl2 = Label::getInstance(50, 50, 300, txtHeight, "MY WORLD IS THE GREATEST EVER!!");
    Button* b1 = Button::getInstance(200, 150, 100, 100, "b1");

    Player* player1 = Player::getInstance(200, 200, 100, 100, "PersonIdle.png");

    
   
    app.add(lbl);
    app.add(lbl2);
    app.add(b1);
    player1->setSpriteDrawArea(0, 0, 124, 124);
    app.addSprite(player1);
    const int w = 20;
    const int h = 12;
    Player* tileMap[w * h];
    for(int y = 0; y < h; y++ )
    {
        for(int x = 0; x < w; x++)
        {
            Player* tile = tileMap[x + (y * w)];
            if(x % 2 == 0)
                tile = Player::getInstance(x*(w), y * (h), w, h, "iconDown.png");
            else
                tile = Player::getInstance(x*(w), y * (h), w, h, "iconUp.png");
            tile->setSpriteDrawArea(0, 0, 32, 32);
            app.addSprite(tile);
        }
    }
    app.run();

 
    return 0;
}