#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <vector>
#include "SDL2/SDL.h"
#include "GameEngine.h"
#include "Component.h"
#include "Sprite.h"

class System
{
    public:
        System(int fps, SDL_Color bg = {255, 255, 0, 255});
        void add(Component* component);
        void addSprite(Sprite * sprite);
        void removeSprite(Sprite * sprite);
        void run();
        ~System();
    
    private:
        void handleKeyDownEvents(const SDL_Event&);
        void handleKeyUpEvents(const SDL_Event&);
        void handleMouseDownEvents(const SDL_Event&);
        void handleMouseUpEvents(const SDL_Event&);
        SDL_Color backgroundColor;
        std::vector<Component*> comps;
        std::vector<Sprite *> sprites;
        std::vector<Sprite *> added;
        std::vector<Sprite *> removed;
        int framesPerSecond;
};


#endif