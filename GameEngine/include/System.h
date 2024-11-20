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
        

        void AddLevel(Level* level);
        void LoadLevel(unsigned int levelIndex);
        
        const std::vector<Sprite*>& GetSpriteCollection() { return sprites; }
        bool GetKeyPressedOnce(const int keyCode) const { return inputComponent.GetKeyPressedOnce(keyCode); }
        bool GetKeyPressed(const int keyCode) const { return inputComponent.GetKeyPressed(keyCode); }
        bool GetMousePressed(const int keyCode) const { return inputComponent.getMousePressed(keyCode); }
        bool Collider2DIsValid(const Sprite& sprite);

        void AppendTextInput(std::string& str);
        const bool& TextInputRecieved() {return textInputRecieved; }

        ~System();
    
    private:
        void AddCollider(Sprite* sprite);
        
        void HandleKeyDownEvents(const SDL_Event&);
        void HandleKeyUpEvents(const SDL_Event&);
        void HandleMouseDownEvents(const SDL_Event&);
        void HandleMouseUpEvents(const SDL_Event&);
        const bool IsColliding(const SDL_Rect& A, const SDL_Rect& B) const;
        
        SDL_Color backgroundColor;
        std::vector<Sprite *> sprites;
        std::vector<Sprite *> added;
        std::vector<Sprite *> removed;
        std::vector<Sprite *> colliderSprites;
        std::vector<Level *> levels;
        Level *currentLevel = nullptr;

        int framesPerSecond;

        bool textInputRecieved;
        std::string strTextInput;

        InputComponent inputComponent;
};



#endif