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
        
        void addSprite(Sprite* sprite);
        void removeSprite(Sprite* sprite);
        void addCollider(Sprite* sprite);
        const std::vector<Sprite*>& GetSpriteCollection() { return sprites; }
        void run();
        ~System();
    
    private:
        void handleKeyDownEvents(const SDL_Event&);
        void handleKeyUpEvents(const SDL_Event&);
        void handleMouseDownEvents(const SDL_Event&);
        void handleMouseUpEvents(const SDL_Event&);
        const bool IsColliding(const SDL_Rect& A, const SDL_Rect& B) const;
        SDL_Color backgroundColor;
        std::vector<Sprite *> sprites;
        std::vector<Sprite *> added;
        std::vector<Sprite *> removed;
        std::vector<Sprite *> colliderSprites;
        int framesPerSecond;
};


#endif