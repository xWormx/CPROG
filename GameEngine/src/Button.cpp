#include "Button.h"


Button* Button::GetInstance(int x, int y, int w, int h, std::string srcImage)
{
    return new Button(x,y,w,h,srcImage);
}

Button::Button(int x, int y, int w, int h, std::string srcImage) : MovableSprite(x,y,w,h,srcImage), pos{x, y}, size{w, h}
{

}

void Button::Tick(System& system)
{
    
}

void Button::SetPosition(Position p)
{
    pos.x = p.x;
    pos.y = p.y;
    setDestRect(p.x, p.y, GetDestRect().w, GetDestRect().h);
}