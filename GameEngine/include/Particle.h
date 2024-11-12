#ifndef PARTICLE_H
#define PARTICLE_H
#include "MovableSprite.h"
#include "Position.h"
#include "System.h"

class Particle : public MovableSprite
{
    public:
        static Particle* getInstance(int x, int y, int w, int h, std::string srcImage, int lt); 
        void tick();
        void draw();
        void SetAppRef(System* app);

        void SetMoveSpeed(int x, int y);

    protected:
        Particle(int x, int y, int w, int h, std::string srcImage, int lt);

    private:
        int lifeTime, lifeTimeStart;
        Position pos;
        Position startPosition;
        int speedX, speedY;
        System *appRef = nullptr;
};


#endif