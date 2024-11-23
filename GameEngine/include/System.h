#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <vector>
#include "SDL2/SDL.h"
#include "Sprite.h"
#include "GameEngine.h"
#include "InputComponent.h"
#include "Level.h"

class Sprite;
class Level;
class System
{
    public:
        System(int fps, SDL_Color bg = {255, 255, 0, 255});
        
        void Run();
        void AddSprite(Sprite* sprite);
        void RemoveSprite(Sprite* sprite);
        void ResolveCollision(Sprite* a, Sprite* b);

        void AddLevel(Level* level);
        void LoadLevel(unsigned int levelIndex);
        
        bool GetKeyPressedOnce(const int keyCode) const { return inputComponent.GetKeyPressedOnce(keyCode); }
        bool GetKeyPressed(const int keyCode) const { return inputComponent.GetKeyPressed(keyCode); }
        bool GetMousePressed(const int keyCode) const { return inputComponent.getMousePressed(keyCode); }

        void AppendTextInput(std::string& str);
        const bool& TextInputRecieved() {return textInputRecieved; }

        ~System();
    
    private:
        void SetCurrentLevel();
        void DrawLevel();
        void HandleKeyDownEvents(const SDL_Event&);
        void HandleKeyUpEvents(const SDL_Event&);
        void HandleMouseDownEvents(const SDL_Event&);
        void HandleMouseUpEvents(const SDL_Event&);
        
        SDL_Color backgroundColor;
        std::vector<Level *> levels;
        Level *currentLevel = nullptr;
        unsigned int levelIndexToLoad;
        bool loadLevelRequested = false;
        int framesPerSecond;

        bool textInputRecieved;
        std::string strTextInput;

        InputComponent inputComponent;
};



#endif