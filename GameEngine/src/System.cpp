#include "System.h"

#define DEBUG 1

System::System(int fps, SDL_Color bg)
{
    backgroundColor = bg;   
    framesPerSecond = fps; 
    //removed.reserve(10);
    std::cout << "System running" << std::endl;
}

void System::AddSprite(Sprite *sprite)
{
    if(sprite != nullptr)
    {
        // Se till så att inte samma pekare läggs till 2 gånger
        // vilket kan hända med textButton som tar Text* och Button* som argument.
        for(Sprite *existingSprite : sprites)
            if(sprite == existingSprite)
                return;

        added.push_back(sprite);
    }


}

void System::RemoveSprite(Sprite* sprite)
{
    if(sprite != nullptr)
    {
        for(Sprite* existingSprite : removed)
        {
            if(sprite == existingSprite)
                return;
        }

        removed.push_back(sprite);
    }
        
}

void System::AddCollider(Sprite *sprite)
{
    if(sprite != nullptr)
    {
        for(Sprite *existingSprite : colliderSprites)
            if(sprite == existingSprite)
                return;

        colliderSprites.push_back(sprite);
    }
    
}


void System::HandleKeyDownEvents(const SDL_Event& event)
{
    inputComponent.setKeyCodePressed(inputComponent.getKeyCodeFromEvent(event));
}

void System::HandleKeyUpEvents(const SDL_Event& event)
{
    inputComponent.setKeyCodeReleased(inputComponent.getKeyCodeFromEvent(event)); 
}

void System::HandleMouseDownEvents(const SDL_Event& event)
{
    
    inputComponent.setMousePressed(inputComponent.GetMouseButtonFromEvent(event));
}

void System::HandleMouseUpEvents(const SDL_Event& event)
{
    
    inputComponent.SetMouseReleased(inputComponent.GetMouseButtonFromEvent(event));
        
}

void System::Run()
{
    SDL_Event event;
    bool quit = false;
    Uint32 tickInterval = 1000 / framesPerSecond;
    
    SDL_StartTextInput();
    while(!quit)
    {
        Uint32 nextTick = SDL_GetTicks() + tickInterval;
        textInputRecieved = false;
        strTextInput.clear();
        inputComponent.ClearSingleInputKeys();

        while(SDL_PollEvent(&event))
        {
            
            switch(event.type)
            {
                case SDL_QUIT: 
		            {
			            quit = true; 
		            } break;

                case SDL_TEXTINPUT:
                    {
                        textInputRecieved = true;    
                        strTextInput += event.text.text;

                    } break;

                case SDL_MOUSEBUTTONDOWN:
                    HandleMouseDownEvents(event);
                    break;

                case SDL_MOUSEBUTTONUP:
                    HandleMouseUpEvents(event);
                    break;
                
                case SDL_KEYDOWN:
                    HandleKeyDownEvents(event); 
                    break;
                
                case SDL_KEYUP:
                    HandleKeyUpEvents(event);
                    break;
            }
        }

        for(Sprite* s : sprites)
            s->Tick(*this);

        for(Sprite* s : colliderSprites)
        {
            for(Sprite* other : colliderSprites)
            {
                if(s != other && IsColliding(s->GetColliderBounds(), other->GetColliderBounds()))
                    s->OnCollision(other, *this);
            }
        }

        for(Sprite* s : added)
            sprites.push_back(s);

        added.clear();

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

        SDL_SetRenderDrawColor(engine.Get_ren(), 
                                backgroundColor.r,
                                backgroundColor.g,
                                backgroundColor.b,
                                backgroundColor.r);

        SDL_RenderClear(engine.Get_ren());
        
 #if DEBUG 
        for(Sprite* s : sprites)
        {
            s->Draw();
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
                SDL_SetRenderDrawColor(engine.Get_ren(), 0xff, 0x00, 0x00, 0xff);
            else
                SDL_SetRenderDrawColor(engine.Get_ren(), 0x00, 0xff, 0x00, 0xff);
            
            s->DEBUGDrawColliderBounds();
           
        }
 #endif

        SDL_RenderPresent(engine.Get_ren());

        int delay = nextTick - SDL_GetTicks();

        if(delay > 0)
            SDL_Delay(delay);

    }

    SDL_StopTextInput();
        
}

void System::AppendTextInput(std::string& str)
{
    str += strTextInput;
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
