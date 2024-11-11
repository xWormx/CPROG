#ifndef MOVABLESPRITE_H
#define MOVABLESPRITE_H

#include "Sprite.h"

class MovableSprite : public Sprite
{
    public:
        void draw() const;
        void setPosition(int x, int y);
        void setSpriteRegion(int x, int y, int w, int h);
    protected:
        MovableSprite(int x, int y, int w, int h, std::string srcImage);
    private:
};


#endif