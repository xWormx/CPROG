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

        void ClearSingleInputKeys();

        SDL_Keycode getKeyCodeFromEvent(const SDL_Event&) const;
        Uint8 GetMouseButtonFromEvent(const SDL_Event&) const;
        
        bool GetKeyPressed(const int keyCode) const;
        bool GetKeyPressedOnce(const int keyCode) const;

        void SetSingleKeyState(const Sint32 keyCode, const bool isPressed);
        bool GetSingleKeyState(const Sint32) const;

        bool getMousePressed(const Uint8 button) const;

    private:
        Sint32 keyCode_1_32   = 0;
        Sint32 keyCode_33_64  = 0;
        Sint32 keyCode_65_96  = 0;
        Sint32 keyCode_97_128 = 0;

        Sint32 keyCode_1_32_SinglePress   = 0;
        Sint32 keyCode_33_64_SinglePress  = 0;
        Sint32 keyCode_65_96_SinglePress  = 0;
        Sint32 keyCode_97_128_SinglePress = 0;

        Sint32 singlePress_State_1_32   = 0;
        Sint32 singlePress_State_33_64  = 0;
        Sint32 singlePress_State_65_96  = 0;
        Sint32 singlePress_State_97_128 = 0;

        Sint32 keyCode_1_32_ReapetPress   = 0;
        Sint32 keyCode_33_64_ReapetPress  = 0;
        Sint32 keyCode_65_96_ReapetPress  = 0;
        Sint32 keyCode_97_128_ReapetPress = 0;

        Uint32 buttonBitPattern = 0;
};

#endif