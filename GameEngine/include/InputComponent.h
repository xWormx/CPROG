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
            
        void setKeyCodePressed(const Sint32 keyCode);
        void setKeyCodeReleased(const Sint32 keyCode);
        void setMousePressed(const Uint32 button);
        void SetMouseReleased(const Uint32 button);

        SDL_Keycode getKeyCodeFromEvent(const SDL_Event&) const;
        Uint8 GetMouseButttonFromEvent(const SDL_Event&) const;
        
        bool GetKeyPressed(const int keyCode) const;
        bool getMousePressed(const Uint8 button) const;

    private:
        Sint32 keyCode_1_32   = 0;
        Sint32 keyCode_33_64  = 0;
        Sint32 keyCode_65_96  = 0;
        Sint32 keyCode_97_128 = 0;

        Uint32 buttonBitPattern = 0;
};

#endif