#ifndef INPUT_H
#define INPUT_H

#include "SDL2/SDL.h"

class InputComponent
{
    public:
        virtual void keyUp(const SDL_Event&){}
        virtual void keyDown(const SDL_Event&){}
        virtual void mouseUp(const SDL_Event&){}
        virtual void mouseDown(const SDL_Event&){}
        SDL_Keycode getKeyCodeFromEvent(const SDL_Event&);
    private:

};

#endif