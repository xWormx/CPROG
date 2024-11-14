#include "System.h"

#define DEBUG 1

System::System(int fps, SDL_Color bg)
{
    backgroundColor = bg;   
    framesPerSecond = fps; 
    removed.reserve(10);
    std::cout << "System running" << std::endl;
}

void System::addSprite(Sprite *sprite)
{
    if(sprite != nullptr)
        added.push_back(sprite);
}

void System::removeSprite(Sprite* s)
{
    if(s != nullptr)
        removed.push_back(s);
}

void System::handleKeyDownEvents(const SDL_Event& event)
{
    for(Sprite *s : sprites)
        s->setKeyCodePressed(s->getKeyCodeFromEvent(event));
}

void System::handleKeyUpEvents(const SDL_Event& event)
{
    for(Sprite* s : sprites)
        s->setKeyCodeReleased(s->getKeyCodeFromEvent(event));
}

void System::handleMouseDownEvents(const SDL_Event& event)
{
    for(Sprite* s : sprites)
    {
        s->setMousePressed(s->getMouseButtonFromEvent(event));
    }
}

void System::handleMouseUpEvents(const SDL_Event& event)
{
    for(Sprite* s : sprites)
    {
        s->setMouseReleased(s->getMouseButtonFromEvent(event));
    }
        
}

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
                case SDL_QUIT: 
		        {
			        quit = true; 
		        } break;
		

                case SDL_MOUSEBUTTONDOWN:
                    handleMouseDownEvents(event);
                    break;

                case SDL_MOUSEBUTTONUP:
                    handleMouseUpEvents(event);
                    break;
                
                case SDL_KEYDOWN:
                    handleKeyDownEvents(event); 
                    break;
                
                case SDL_KEYUP:
                    handleKeyUpEvents(event);
                    break;
            }
        }

        for(Sprite* s : sprites)
            s->tick(*this);

        for(Sprite* s : added)
            sprites.push_back(s);

        added.clear();

        for(Sprite* s : removed)
        {
            for(std::vector<Sprite*>::iterator i = sprites.begin(); i != sprites.end();)
            {
                if(*i == s)
                {
                    delete *i;
                    i = sprites.erase(i);
                }    
                else
                    i++;
            }
        }
        removed.clear();

        SDL_SetRenderDrawColor(engine.get_ren(), 
                                backgroundColor.r,
                                backgroundColor.g,
                                backgroundColor.b,
                                backgroundColor.r);
        SDL_RenderClear(engine.get_ren());
        

        for(Sprite* sprite : sprites)
        {
            sprite->draw();

           #if DEBUG 
            bool didCollide = false;
            
            for(Sprite* collider : sprites)
            {
                if(sprite != collider)
                {
                    if(sprite->DEBUGDidCollide(*collider))
                    {
                        didCollide = true;
                        break;
                    }
                    
                }
                
            }
            
            if(didCollide)
                SDL_SetRenderDrawColor(engine.get_ren(), 0xff, 0x00, 0x00, 0xff);
            else
                SDL_SetRenderDrawColor(engine.get_ren(), 0x00, 0xff, 0x00, 0xff);
            
            sprite->DEBUGDrawLineFrame();
            #endif
        }


        SDL_RenderPresent(engine.get_ren());

        int delay = nextTick - SDL_GetTicks();

        if(delay > 0)
            SDL_Delay(delay);

    }
        
}

System::~System()
{
    std::cout << "System shutdown" << std::endl;       
}
