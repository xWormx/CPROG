#ifndef MOVABLESPRITE_H
#define MOVABLESPRITE_H

#include "Sprite.h"
#include "System.h"
#include "Position.h"
#include "Dimension.h"

class MovableSprite : public Sprite
{
    public:
        void Draw() const;
        void setPosition(int x, int y);
        void Move(int dx, int dy);
        int AnimateSprite(Position frameStart, Dimension frameSize, unsigned int maxFrames, unsigned int animSpeed);
        void setSpriteRegion(int x, int y, int w, int h);
        virtual const bool CheckCollision(Sprite* other) const { return false; }
    protected:
        MovableSprite(int x, int y, int w, int h, std::string srcImage);
        MovableSprite(int x, int y, int w, int h);
    private:
        Position lastAnimationFrameStart = {};
        unsigned int animationFrame = 0;
        unsigned int animationTick = 0;
};


#endif