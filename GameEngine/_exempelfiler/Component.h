#ifndef COMPONENT_H
#define COMPONENT_H

#include "SDL2/SDL.h"

class Component
{
    public:
        ~Component();
        virtual void keyDown(const SDL_Event&){}
        virtual void keyUp(const SDL_Event&){}
        virtual void mouseDown(const SDL_Event&){}
        virtual void mouseUp(const SDL_Event&){}
        virtual void Draw() const = 0;
        virtual void Tick() = 0;
        virtual void setPosition(SDL_Point newPosition){}
        SDL_Rect* getRect();
    protected:
        Component(int x, int y, int w, int h);
        const SDL_Rect& getRect() const { return rect; }
    private:
        SDL_Rect rect;
};

#endif