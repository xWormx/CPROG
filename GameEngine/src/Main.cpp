#include "System.h"
#include "Label.h"
#include "Button.h"
//#include "SDL2/SDL.h"

#define FPS 60

class Player : public Sprite
{
    public: 
        static Player* getInstance(int x, int y, int h, int w, std::string srcImage)
        {
            return new Player(x, y, w, h, srcImage);
        }

        void setSpriteDrawArea(int x, int y, int w, int h)
        {
            Sprite::setAreaRectToDraw(x, y, w, h);
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

            
            Sprite::setPosition(xPos, yPos);
        }

        bool keyPressed(const int keyCode)
        {
            return InputComponent::getKeyCodePressed(keyCode);
        }

    protected:
        Player(int x, int y, int h, int w, std::string srcImage) : Sprite(x,y,w,h,srcImage)
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

        bool move;
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
    app.run();

 
    return 0;
}