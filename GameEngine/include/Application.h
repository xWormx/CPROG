#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <vector>
#include "SDL2/SDL.h"
#include "GameEngine.h"
#include "Component.h"
#include "Sprite.h"

class Application
{
    public:
        Application(int fps, SDL_Color bg = {255, 255, 0, 255});
        void add(Component* component);
        void addSprite(Sprite * sprite);
        void run();
        ~Application();
    
    private:
        void handleKeyDownEvents(const SDL_Event&);
        SDL_Color backgroundColor;
        std::vector<Component*> comps;
        std::vector<Sprite *> sprites;
        int framesPerSecond;
};


#endif