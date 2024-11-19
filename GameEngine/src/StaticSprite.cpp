#include "StaticSprite.h"

StaticSprite::StaticSprite(int x, int y, int w, int h, std::string srcImage) : Sprite(x,y,w,h,srcImage)
{
}

void StaticSprite::draw() const
{
    SDL_RenderCopy(engine.Get_ren(), const_cast<SDL_Texture*>(getTexture()), &getSrcRect(), &getDestRect());
}