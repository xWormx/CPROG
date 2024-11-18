#include "Button.h"


Button* Button::getInstance(int x, int y, int w, int h, std::string srcImage)
{
    return new Button(x,y,w,h,srcImage);
}

Button::Button(int x, int y, int w, int h, std::string srcImage) : MovableSprite(x,y,w,h,srcImage), pos{x, y}, size{w, h}
{

}

void Button::tick(System& system)
{
    
}

void Button::SetPosition(Position p)
{
    setDestRect(p.x, p.y, getDestRect().w, getDestRect().h);
}