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

            //int w, h;
            //SDL_GetWindowSize(engine.get_window(), &w, &h);
            //static SDL_Rect viewPort = {0, 0, w, h};
            //int err = SDL_RenderSetViewport(engine.get_ren(), &viewPort);
            //if(err < 0)
            //    std::cout << "Viewport error: " << SDL_GetError() << std::endl;
                
            if(keyPressed('d') || InputComponent::getMousePressed(SDL_BUTTON_LEFT))
            {
            //    if(viewPort.x > 0 && tick % 20 == 0)
            //        viewPort.x--;
                
                xPos++;
            }
            if(keyPressed('a'))
            {
                xPos--;
            //    if(tick % 20 == 0)
            //        viewPort.x++;
            }
            if(keyPressed('w'))
            {
                yPos--;
            }
            if(keyPressed('s'))
            {
                yPos++;
            }

            
            MovableSprite::setPosition(xPos, yPos);
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
    
    int txtHeight = 16;
    Label* lbl = Label::getInstance(0, 0, 32, txtHeight, "HEJ");
    Label* lbl2 = Label::getInstance(50, 50, 300, txtHeight, "MY WORLD IS THE GREATEST EVER!!");
    Button* b1 = Button::getInstance(200, 150, 100, 100, "b1");

    Player* player1 = Player::getInstance(200, 200, 300, 300, "PersonIdle.png");
    player1->setSpriteRegion(0, 0, 124, 124);
    
    const int mapW = 100;
    const int mapH = 100;
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
            app.addSprite(tile);
        }
    }

    app.add(lbl);
    app.add(lbl2);
    app.add(b1);
    app.addSprite(player1);
    
    app.run();

 
    return 0;
}