#include "Particle.h"


Particle* Particle::getInstance(int x, int y, int w, int h, std::string srcImage, int lt) 
{
    return new Particle(x,y,w,h,srcImage, lt);
}

Particle::Particle(int x, int y, int w, int h, std::string srcImage, int lt) : MovableSprite(x,y,w,h,srcImage), lifeTime(lt), lifeTimeStart(lt), pos{x,y}, startPosition{x,y}
{
}

void Particle::draw()
{
    SDL_RenderCopy(engine.get_ren(), texture, &getSrcRect(), &getDestRect());
}

void Particle::tick()
{
    lifeTime--;
    if(lifeTime < 0)
    {
        lifeTime = lifeTimeStart;
        pos = startPosition;
        appRef->removeSprite(this);
    }
    else
    {
        pos.x += speedX;
        pos.y += speedY;
        setPosition(pos.x, pos.y);    
    }
}

void Particle::SetAppRef(System *app)
{
    appRef = app;
}

void Particle::SetMoveSpeed(int x, int y)
{
    speedX = x;
    speedY = y;
}