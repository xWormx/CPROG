#include "TextFragment.h"


TextFragment* TextFragment::GetInstance(int x, int y, int w, int h, std::string text, SDL_Color c)
{
    return new TextFragment(x, y, w, h, text, c);
}

TextFragment::TextFragment(int x, int y, int w, int h, std::string text, SDL_Color c) : MovableSprite(x,y,w,h), strText(text), color(c)
{
    SDL_Surface *surface = TTF_RenderText_Solid(engine.Get_font(), text.c_str(), c);

    std::string error;
    if(surface == NULL)
    {
        error = SDL_GetError();
        throw std::runtime_error("Couldn't load TTF surface for text" + error);
    }
    
    if(textTexture == nullptr)
        SDL_DestroyTexture(textTexture);

    textTexture = SDL_CreateTextureFromSurface(engine.Get_ren(), surface);
    if(textTexture == nullptr)
    {
        error = SDL_GetError();
        throw std::runtime_error("Couldn't load Texture from surface" + error);
    }

    SDL_FreeSurface(surface);

    int queryResult = SDL_QueryTexture(textTexture, nullptr, nullptr, &srcRect.w, &srcRect.h);
    if(queryResult != 0)
    {
        error = SDL_GetError();
        throw std::runtime_error("Couldn't query Texture - error code: " + queryResult );
    }

    srcRect.x = 0;
    srcRect.y = 0;
}

void TextFragment::Draw() const
{
    SDL_RenderCopy(engine.Get_ren(), textTexture, &GetSrcRect(), &GetDestRect());
}

void TextFragment::Tick(System& system)
{
    
}

void TextFragment::SetText(std::string s)
{
    strText = s;
    try
    {
        std::string error;
        SDL_Surface* surface = TTF_RenderText_Solid(engine.Get_font(), strText.c_str(), color);    
        if(surface == NULL)
        {
            error = SDL_GetError();
            throw std::runtime_error("Couldn't load surface for text" + error);
        }

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

void TextFragment::SetPosition(Position p)
{
    pos.x = p.x;
    pos.y = p.y;
    setDestRect(p.x, p.y, GetDestRect().w, GetDestRect().h);
}