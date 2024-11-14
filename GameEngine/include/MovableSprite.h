#ifndef MOVABLESPRITE_H
#define MOVABLESPRITE_H

#include "Sprite.h"
#include "System.h"
class MovableSprite : public Sprite
{
    public:
        void draw() const;
        void setPosition(int x, int y);
        void setSpriteRegion(int x, int y, int w, int h);
        virtual const bool CheckCollision(Sprite* other) const { return false; }
    protected:
        MovableSprite(int x, int y, int w, int h, std::string srcImage);
    private:

};


#endif