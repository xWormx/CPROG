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
        
        std::string targetString = "player";

        // Sorterar för att spelaren skall uppdateras först så att ALLA tiles flyttas om player befinner sig i 
        // windowBounds, annars så uppdateras bara de tiles som kommer efter player i vectorn och då sker tearing mellan tilesen
        // så de separeras.
        auto it = std::find_if(currentLevel->GetSprites().begin(), currentLevel->GetSprites().end(), [targetString](Sprite* s)
        {
            return s->GetTagName() == targetString;
        });


        Sprite* s = nullptr;
        if (it != currentLevel->GetSprites().end()) {
            s = *it;  // Get the sprite that matches the target string

            // Step 2: Get the first sprite in the sprite list
            Sprite* firstSprite = currentLevel->GetSprites().front();

            // Step 3: Swap the found sprite with the first sprite in the list
            if (firstSprite != s) {  // Only swap if it's not already the first sprite
                // Swap the two sprites in the list
                std::iter_swap(it, currentLevel->GetSprites().begin());
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


    size_t n = currentLevel->GetSprites().size();
    
    // Bubble Sort algorithm
    for (size_t i = 0; i < n - 1; ++i) {
        for (size_t j = 0; j < n - i - 1; ++j) {
            // Check if pointers are valid before comparing
            Sprite* a = currentLevel->GetSprites()[j];
            Sprite* b = currentLevel->GetSprites()[j + 1];

            if (a == nullptr) {
                std::cerr << "Warning: Invalid pointer at index " << j << " (a is nullptr)" << std::endl;
                continue;  // Skip this comparison
            }
            if (b == nullptr) {
                std::cerr << "Warning: Invalid pointer at index " << j + 1 << " (b is nullptr)" << std::endl;
                continue;  // Skip this comparison
            }

            // Compare first by layerTagName
            if(a->GetLayerTag() != "ground" && b->GetLayerTag() == "ground")
            {
                std::swap(currentLevel->GetSprites()[j], currentLevel->GetSprites()[j+1]);
                continue;
            }
            
            if(b->GetLayerTag() != "ground" && a->GetLayerTag() == "ground")
                continue;

            // Compare y-values of valid sprites
            if(a->GetLayerTag() != "ground" && b->GetLayerTag() != "ground")
            {
                if (a->GetDestRect().y > b->GetDestRect().y) 
                {
                    // Swap sprites if a->getY() > b->getY()
                    std::swap(currentLevel->GetSprites()[j], currentLevel->GetSprites()[j + 1]);
                }
            }
            
        }


    }

    for(Sprite* s : currentLevel->GetSprites())
    {
        s->Draw();
#if DEBUG 
        s->DEBUGDrawSpriteBounds();
#endif
    }

#if DEBUG    
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

void System::ResolveCollision(Sprite* a, Sprite* b)
{
    int aX = a->GetColliderBounds().x;
    int aY = a->GetColliderBounds().y;
    int aW = a->GetColliderBounds().w;
    int aH = a->GetColliderBounds().h;
    
    int bX = b->GetColliderBounds().x;
    int bY = b->GetColliderBounds().y;
    int bW = b->GetColliderBounds().w;
    int bH = b->GetColliderBounds().h;
    
    int overlapX;
    int overlapY;

    if(aX < bX)
        overlapX = (aX + aW) - bX;
    else
        overlapX = (bX + bW) - aX;

    if(aY < bY)
        overlapY = (aY + aH) - bY;
    else
        overlapY = (bY + bH) - aY;

    int drX = a->GetDestRect().x;
    int drY = a->GetDestRect().y;
    int drW = a->GetDestRect().w;
    int drH = a->GetDestRect().h;

    if(a->GetDy() != 0 && a->GetDx() != 0)
        std::cout << "diagonal movement!\n";
    if(overlapX == overlapY)
        std::cout << "EQUAL!\n";

    int pushBackX = std::abs(a->GetDx()); 
    int pushBackY = std::abs(a->GetDy()); 
    if(overlapX < overlapY)
    {
        if(aX < bX)
        {
            pushBackX += std::abs(b->GetDx());
            a->SetColliderBounds({aX - pushBackX, aY, aW, aH});
            a->setDestRect(drX - pushBackX, drY, drW, drH);
            
        }
        else
        {
            a->SetColliderBounds({aX + pushBackX, aY, aW, aH});
            a->setDestRect(drX + pushBackX, drY, drW, drH);
        }
        return;
    }
    
    if(aY > bY)
    {
        a->SetColliderBounds({aX, aY + pushBackY, aW, aH});
        a->setDestRect(drX, drY + pushBackY, drW, drH);
    }
    else
    {
        a->SetColliderBounds({aX, aY - pushBackY, aW, aH});
        a->setDestRect(drX, drY - pushBackY, drW, drH);
    }
    //std::cout << "OverlapX: " << overlapX << ", OverlapY: " << overlapY << "\n";
    //std::cout << "dX: " << a->GetDx() << ", dY: " << a->GetDy() << "\n";
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
