#include "Application.h"
#include "Label.h"
#include "Button.h"
#include "SDL2/SDL.h"

#define FPS 60

class Player : public Sprite
{
    public: 
        Player(int x, int y, int h, int w, std::string srcImage)
        {
            //this->sprite = Sprite::getInstance(x, y, w, h, srcImage);
        }
        Sprite *getSprite() { return sprite; }
    private:
        Sprite *sprite;

};

int main(int argv, char **argc)
{
    
    Application app(FPS, {255, 150, 70, 255});
    
    int txtHeight = 16;
    Label* lbl = Label::getInstance(0, 0, 32, txtHeight, "HEJ");
    Label* lbl2 = Label::getInstance(50, 50, 300, txtHeight, "MY WORLD IS THE GREATEST EVER!!");
    Button* b1 = Button::getInstance(200, 150, 100, 100, "b1");
    Sprite* sprite = Sprite::getInstance(100, 100, 64, 64, "bg.jpg");
    

    Player player1(400, 400, 100, 100, "bg.jpg");
    app.add(lbl);
    app.add(lbl2);
    app.add(b1);
    app.addSprite(sprite);
    app.addSprite(player1.getSprite());
    app.run();

 
    return 0;
}