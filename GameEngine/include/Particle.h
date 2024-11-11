#ifndef PARTICLE_H
#define PARTICLE_H
#include "MovableSprite.h"

class Particle : public MovableSprite
{
    public:
        static Particle* getInstance(int x, int y, int w, int h, std::string srcImage, int lt); 
        void tick();
        void draw();

    protected:
        Particle(int x, int y, int w, int h, std::string srcImage, int lt);

    private:
        int lifeTime;

};


#endif