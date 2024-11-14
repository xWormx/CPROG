#ifndef STATICSPRITE_H
#define STATICSPRITE_H

#include "Sprite.h"
#include "System.h"

class StaticSprite : public Sprite
{
    public:
        void draw() const;
    protected:
        StaticSprite(int x, int y, int w, int h, std::string srcImage);
    private:
};

#endif