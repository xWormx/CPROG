#include "TextFragment.h"


TextFragment* TextFragment::getInstance(int x, int y, int w, int h, std::string text, SDL_Color c)
{
    return new TextFragment(x, y, w, h, text, c);
}

TextFragment::TextFragment(int x, int y, int w, int h, std::string text, SDL_Color c) : Sprite(x,y,w,h)
{
    SDL_Surface *surface = TTF_RenderText_Solid(engine.get_font(), text.c_str(), c);

    std::string error;
    if(surface == NULL)
    {
        error = SDL_GetError();
        throw std::runtime_error("Couldn't load TTF surface for text" + error);
    }
    
    if(textTexture == nullptr)
        SDL_DestroyTexture(textTexture);

    textTexture = SDL_CreateTextureFromSurface(engine.get_ren(), surface);
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

}

void TextFragment::draw() const
{
    SDL_RenderCopy(engine.get_ren(), textTexture, &getSrcRect(), &getDestRect());
}

void TextFragment::tick(System& system)
{
    
}