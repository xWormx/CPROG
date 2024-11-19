#ifndef PARTICLE_H
#define PARTICLE_H
#include "MovableSprite.h"
#include "Position.h"
#include "Dimension.h"
#include "System.h"

class Particle : public MovableSprite
{
    public:
        static Particle* GetInstance(int x, int y, int w, int h, std::string srcImage, int lt); 
        void Tick(System& system);
        void Draw();

        void SetAppRef(System* app);
        void SetMoveSpeed(int x, int y);

        void OnCollision(Sprite* other, System& system);

        const Dimension& GetSize() const;
        const Position& GetPosition() const;

        void DestroySelf();

    protected:
        Particle(int x, int y, int w, int h, std::string srcImage, int lt);

    private:
        int lifeTime, lifeTimeStart;
        Position pos;
        Position startPosition;
        Dimension size;
        int speedX, speedY;
        System *appRef = nullptr;
};


#endif