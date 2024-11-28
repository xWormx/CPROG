#include "MovableSprite.h"


MovableSprite::MovableSprite(int x, int y, int w, int h, std::string srcImage) : Sprite(x,y,w,h,srcImage)
{

}

MovableSprite::MovableSprite(int x, int y, int w, int h) : Sprite(x,y,w,h)
{

}

void MovableSprite::Draw() const
{
    SDL_RenderCopy(engine.Get_ren(), texture, &GetSrcRect(), &GetDestRect());
}

void MovableSprite::setSpriteRegion(int x, int y, int w, int h)
{
    setSrcRect(x, y, w, h);
}

int MovableSprite::AnimateSprite(Position frameStart, Dimension frameSize, unsigned int maxFrames, unsigned int animSpeed)
{
    if(frameStart.x != lastAnimationFrameStart.x || frameStart.y != lastAnimationFrameStart.y)
    {
        animationTick = 0;
        animationFrame = 0;
    }

    if(animationTick++ % animSpeed == 0)
    {
        if(animationFrame >= maxFrames)
        {
            animationFrame = 0;
        }

        setSpriteRegion((frameStart.x * frameSize.w) + (animationFrame * frameSize.w), 0, frameSize.w, frameSize.h);
        animationFrame++;

    }
    lastAnimationFrameStart = frameStart;
    return animationFrame;
}

void MovableSprite::Move(int dx, int dy)
{
    if(dy == 0 && dx == 0)
        int i = 0;
        
    SetMovementDirection(dx, dy);
    destRect.x += dx;
    destRect.y += dy;
}

void MovableSprite::setPosition(int x, int y)
{
    setDestRect(x, y, GetDestRect().w, GetDestRect().h);
}




