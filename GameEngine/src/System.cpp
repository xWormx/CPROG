#include "System.h"

System::System(int fps, SDL_Color bg)
{
    backgroundColor = bg;   
    framesPerSecond = fps; 
    std::cout << "System running" << std::endl;
}

void System::add(Component* component)
{
    comps.push_back(component);
}

void System::addSprite(Sprite *sprite)
{
    sprites.push_back(sprite);
}

void System::handleKeyDownEvents(const SDL_Event& event)
{
    for(Component *c : comps)
        c->keyDown(event);

    for(Sprite *s : sprites)
        s->setKeyCodePressed(s->getKeyCodeFromEvent(event));
}

void System::handleKeyUpEvents(const SDL_Event& event)
{
    for(Component* c : comps)
        c->keyUp(event);

    for(Sprite* s : sprites)
        s->setKeyCodeReleased(s->getKeyCodeFromEvent(event));
}

//void System::handleMouseDownEvents(const SDL_Event& event);
//{
//
//}
//
//void System::handleMouseUpEvents(const SDL_Event& event);
//{
//    for(Sprite* s : sprite)
//        s->
//}

void System::run()
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
                    handleKeyUpEvents(event);
                    break;
            }
        }

        for(Component* c : comps)
            c->tick();

        for(Sprite* s : sprites)
            s->tick();

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

System::~System()
{
    comps.clear();

    std::cout << "System shutdown" << std::endl;       
}