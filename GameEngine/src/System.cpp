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

void System::addCollider(Sprite *sprite)
{
    if(sprite != nullptr)
        colliderSprites.push_back(sprite);
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

        for(Sprite* s : colliderSprites)
        {
            for(Sprite* other : colliderSprites)
            {
                if(s != other && IsColliding(s->GetColliderBounds(), other->GetColliderBounds()))
                    s->OnCollision(other);
            }
        }
            

        for(Sprite* s : removed)
        {       
            for(std::vector<Sprite*>::iterator i = sprites.begin(); i != sprites.end();)
            {
                if(*i == s)
                {
                    i = sprites.erase(i);
                }    
                else
                    i++;
            }

            for(std::vector<Sprite*>::iterator j = colliderSprites.begin(); j != colliderSprites.end();)
            {
                if(*j == s)
                    j = colliderSprites.erase(j);
                else
                    j++;
            }

            delete s;
        }

        removed.clear();

        SDL_SetRenderDrawColor(engine.get_ren(), 
                                backgroundColor.r,
                                backgroundColor.g,
                                backgroundColor.b,
                                backgroundColor.r);

        SDL_RenderClear(engine.get_ren());
        
 #if DEBUG 
        for(Sprite* s : sprites)
        {
            s->draw();
            s->DEBUGDrawSpriteBounds();
        }

        for(Sprite* s : colliderSprites)
        {
            // O(n^2) kollisionsdetektering just nu....
          
            bool didCollide = false;
            
            for(Sprite* collider : colliderSprites)
            {
                if(s != collider)
                {
                    if(s->DEBUGDidCollide(*collider))
                    {
                        didCollide = true;
                    }   
                }
            }
            
            if(didCollide)
                SDL_SetRenderDrawColor(engine.get_ren(), 0xff, 0x00, 0x00, 0xff);
            else
                SDL_SetRenderDrawColor(engine.get_ren(), 0x00, 0xff, 0x00, 0xff);
            
            s->DEBUGDrawColliderBounds();
           
        }
 #endif

        SDL_RenderPresent(engine.get_ren());

        int delay = nextTick - SDL_GetTicks();

        if(delay > 0)
            SDL_Delay(delay);

    }
        
}

const bool System::IsColliding(const SDL_Rect& A, const SDL_Rect& B) const
{
    // y goes downwards so bottom is y + h;
    int left = A.x, right = A.x + A.w,
        top = A.y, bottom = A.y + A.h;
    
    int otherLeft = B.x, otherRight  = B.x + B.w,
        otherTop  = B.y, otherBottom = B.y + B.h;

    if(left < otherRight && right > otherLeft &&
        top < otherBottom && bottom > otherTop )
        return true;
    
    return false;
}

System::~System()
{
    std::cout << "System shutdown" << std::endl;       
}
