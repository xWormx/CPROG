#include "TextField.h"


TextField* TextField::GetInstance(int x, int y, SDL_Color c)
{
    return new TextField(x,y,c);
}

TextField::TextField(int x, int y, SDL_Color c) : Sprite(x,y,0,0), pos{x,y}, size{0,0}, color(c)
{
}

void TextField::Draw() const
{
    if(textTexture != nullptr)
        SDL_RenderCopy(engine.Get_ren(), textTexture, &GetSrcRect(), &GetDestRect());
}

void TextField::Tick(System& system)
{
    if(system.TextInputRecieved())
    {
        system.AppendTextInput(currentText);

        RenderNewTextInput();
    }
    
    if(system.GetKeyPressedOnce(SDLK_BACKSPACE))
    {
        if(currentText.size() > 0)
            currentText.pop_back();
        RenderNewTextInput();
    }
}


void TextField::UpdateTextInput(System& system)
{

}

void TextField::RenderNewTextInput()
{
    try
    {
        // Kommer inte rendera den nya texten om den är tom, så " " gör att den renderas,
        // men är osynlig.
        if(currentText.empty()) { currentText = " ";}
        
        std::string error;
        SDL_Surface* surface = TTF_RenderText_Solid(engine.Get_font(), currentText.c_str(), color);    
        if(surface == NULL)
        {
            error = SDL_GetError();
            throw std::runtime_error("Couldn't load surface for text" + error);
        }
        destRect.w = surface->w;
        destRect.h = surface->h;
        size.w = surface->w;
        size.h = surface->h;

        if(textTexture != nullptr)
            SDL_DestroyTexture(textTexture);

        textTexture = SDL_CreateTextureFromSurface(engine.Get_ren(), surface);
        if(textTexture == NULL)
        {   
            error = SDL_GetError();
            throw std::runtime_error("Couldn't texture from surface" + error);
        }

        SDL_Rect r = {};
        int result = SDL_QueryTexture(textTexture, nullptr, nullptr, &r.w, &r.h);
        if(result < 0) 
        {
             error = SDL_GetError();
             throw std::runtime_error("Couldn't query texture" + error);
        }
        
        srcRect.x = 0;
        srcRect.y = 0;
        srcRect.w = r.w;
        srcRect.h = r.h;
        SDL_FreeSurface(surface);

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}