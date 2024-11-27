#ifndef STATICSPRITE_H
#define STATICSPRITE_H

#include "Sprite.h"
#include "System.h"

class StaticSprite : public Sprite
{
    public:
        static StaticSprite* GetInstance(int x, int y, int w, int h, std::string srcImage);
        void Draw() const;
        void Tick(System& system);
    protected:
        StaticSprite(int x, int y, int w, int h, std::string srcImage);
    private:
};

#endif