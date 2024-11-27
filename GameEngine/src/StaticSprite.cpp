#include "StaticSprite.h"

StaticSprite* StaticSprite::GetInstance(int x, int y, int w, int h, std::string srcImage)
{
    return new StaticSprite(x,y,w,h,srcImage);
}

StaticSprite::StaticSprite(int x, int y, int w, int h, std::string srcImage) : Sprite(x,y,w,h,srcImage)
{
}

void StaticSprite::Draw() const
{
    SDL_RenderCopy(engine.Get_ren(), const_cast<SDL_Texture*>(getTexture()), &GetSrcRect(), &GetDestRect());
}

void StaticSprite::Tick(System& system)
{

}