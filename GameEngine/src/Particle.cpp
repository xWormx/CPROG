#include "Particle.h"


Particle* Particle::getInstance(int x, int y, int w, int h, std::string srcImage, int lt) 
{
    return new Particle(x,y,w,h,srcImage, lt);
}

Particle::Particle(int x, int y, int w, int h, std::string srcImage, int lt) : MovableSprite(x,y,w,h,srcImage), lifeTime(lt)
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

    }
    else
    {

    }
}