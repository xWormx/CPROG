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
        void setKeyCodePressed(const Sint32 keyCode);
        void setKeyCodeReleased(const Sint32 keyCode);
        bool getKeyCodePressed(const int keyCode) const;
    private:
    Sint32 keyCode_1_32   = 0;
    Sint32 keyCode_33_64  = 0;
    Sint32 keyCode_65_96  = 0;
    Sint32 keyCode_97_128 = 0;

};

#endif