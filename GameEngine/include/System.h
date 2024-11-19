#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <vector>
#include "SDL2/SDL.h"
#include "Sprite.h"
#include "GameEngine.h"


class Sprite;
class System
{
    public:
        System(int fps, SDL_Color bg = {255, 255, 0, 255});
        
        void AddSprite(Sprite* sprite);
        void RemoveSprite(Sprite* sprite);
        void AddCollider(Sprite* sprite);
        const std::vector<Sprite*>& GetSpriteCollection() { return sprites; }
        void Run();

        void AppendTextInput(std::string& str);

        const bool& TextInputRecieved() {return textInputRecieved; }
        ~System();
    
    private:
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
        int framesPerSecond;

        bool textInputRecieved;
        std::string strTextInput;
};


#endif