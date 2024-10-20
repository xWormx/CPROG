#include "Application.h"

Application::Application(int fps, SDL_Color bg)
{
    backgroundColor = bg;   
    framesPerSecond = fps; 
    std::cout << "Application running" << std::endl;
}

void Application::add(Component* component)
{
    comps.push_back(component);
}

void Application::addSprite(Sprite *sprite)
{
    sprites.push_back(sprite);
}

void Application::handleKeyDownEvents(const SDL_Event& event)
{
    for(Component *c : comps)
        c->keyDown(event);

    for(Sprite *s : sprites)
        s->keyDown(event);
}

void Application::run()
{
    SDL_Event event;
    bool quit = false;
    Uint32 tickInterval = 1000 / framesPerSecond;

    while(!quit)
    {
        Uint32 nextTick = SDL_GetTicks() + tickInterval;

        while(SDL_PollEvent(&event))
        {
            //
            switch(event.type)
            {
                case SDL_QUIT: quit = true; break;
                
                case SDL_MOUSEBUTTONDOWN:
                    for(Component* c : comps)
                        c->mouseDown(event);
                    break;

                case SDL_MOUSEBUTTONUP:
                    for(Component* c : comps)
                        c->mouseUp(event);
                    break;
                
                case SDL_KEYDOWN:
                    handleKeyDownEvents(event);
                    break;
                
                case SDL_KEYUP:
                    for(Component* c : comps)
                        c->keyUp(event);
                    break;
            }
        }

        for(Component* c : comps)
            c->tick();

        SDL_SetRenderDrawColor(engine.get_ren(), 
                                backgroundColor.r,
                                backgroundColor.g,
                                backgroundColor.b,
                                backgroundColor.r);
        SDL_RenderClear(engine.get_ren());
        
        
        for(Component* c : comps)
        {
            c->draw();
        }

        for(Sprite* sprite : sprites)
        {
            sprite->draw();
        }

        SDL_RenderPresent(engine.get_ren());

        int delay = nextTick - SDL_GetTicks();

        if(delay > 0)
            SDL_Delay(delay);
    }
        
}

Application::~Application()
{
    comps.clear();

    std::cout << "Application shutdown" << std::endl;       
}