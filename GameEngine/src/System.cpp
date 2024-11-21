#include "System.h"

#define DEBUG 1

System::System(int fps, SDL_Color bg)
{
    backgroundColor = bg;   
    framesPerSecond = fps; 
    //removed.reserve(10);
    std::cout << "System running" << std::endl;
}

void System::AddLevel(Level *level)
{
    if(level != nullptr)
    {
        for(Level* l : levels)
        if(l->GetLevelIndex() == level->GetLevelIndex())
        {
            std::string errorMsg = "There's already a level with index: " + std::to_string(level->GetLevelIndex()) + "\n";
            throw std::runtime_error(errorMsg);
        }
            
    
        levels.push_back(level);
        // Laddar första leveln som default när den läggs till.
        if(levels.size() == 1)
        {
            LoadLevel(level->GetLevelIndex());
            SetCurrentLevel();
        }
            
    }
    else
    {
        throw std::runtime_error("Level is invalid, can't added it to the system!\n");
    }
    
}

void System::LoadLevel(unsigned int levelIndex)
{
    loadLevelRequested = true;
    levelIndexToLoad = levelIndex;
}

void System::SetCurrentLevel()
{
    for(Level* l : levels)
    {
        if(l->GetLevelIndex() == levelIndexToLoad)
        {
            currentLevel = l;
            loadLevelRequested = false;
        }
            
    }
}

void System::AddSprite(Sprite *sprite)
{
    currentLevel->AddSprite(sprite);
}

void System::RemoveSprite(Sprite* sprite)
{
    currentLevel->RemoveSprite(sprite);   
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

        if(loadLevelRequested)
            SetCurrentLevel();  

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

        currentLevel->Update(*this); 
        DrawLevel();
 
        int delay = nextTick - SDL_GetTicks();

        if(delay > 0)
            SDL_Delay(delay);

    }

    SDL_StopTextInput();
        
}

void System::DrawLevel()
{
    SDL_SetRenderDrawColor(engine.Get_ren(), 
                            backgroundColor.r,
                            backgroundColor.g,
                            backgroundColor.b,
                            backgroundColor.r);
    
    SDL_RenderClear(engine.Get_ren());

#if DEBUG 
    
    for(Sprite* s : currentLevel->GetSprites())
    {
        s->Draw();
        s->DEBUGDrawSpriteBounds();
    }
    
    for(Sprite* s : currentLevel->GetColliders())
    {
        // O(n^2) kollisionsdetektering just nu....
      
        bool didCollide = false;
        
        for(Sprite* collider : currentLevel->GetColliders())
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

}

void System::AppendTextInput(std::string& str)
{
    str += strTextInput;
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

System::~System()
{
    std::cout << "System shutdown" << std::endl;       
}
