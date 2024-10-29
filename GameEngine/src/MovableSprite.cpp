#include "MovableSprite.h"


MovableSprite::MovableSprite(int x, int y, int w, int h, std::string srcImage) : Sprite(x,y,w,h,srcImage)
{

}

void MovableSprite::draw() const
{
    SDL_RenderCopy(engine.get_ren(), const_cast<SDL_Texture*>(getTexture()), &getSrcRect(), &getDestRect());
}

void MovableSprite::setPosition(int x, int y)
{
    setDestRect(x, y, getDestRect().w, getDestRect().h);
}