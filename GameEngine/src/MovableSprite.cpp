#include "MovableSprite.h"


MovableSprite::MovableSprite(int x, int y, int w, int h, std::string srcImage) : Sprite(x,y,w,h,srcImage)
{

}

MovableSprite::MovableSprite(int x, int y, int w, int h) : Sprite(x,y,w,h)
{

}

void MovableSprite::draw() const
{
    SDL_RenderCopy(engine.get_ren(), texture, &getSrcRect(), &getDestRect());
}

void MovableSprite::setSpriteRegion(int x, int y, int w, int h)
{
    setSrcRect(x, y, w, h);
}

void MovableSprite::AnimateSprite(Position frameStart, Dimension frameSize, unsigned int maxFrames, unsigned int animSpeed)
{
    if(animationTick++ % animSpeed == 0)
    {
        setSpriteRegion((frameStart.x * frameSize.w) + (animationFrame * frameSize.w), 0, frameSize.w, frameSize.h);
        animationFrame++;
        if(animationFrame > maxFrames)
        {
            animationFrame = 0;
        }
    }
}


void MovableSprite::setPosition(int x, int y)
{
    setDestRect(x, y, getDestRect().w, getDestRect().h);
}




