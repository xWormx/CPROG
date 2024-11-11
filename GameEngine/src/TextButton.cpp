#include "TextButton.h"
#include <stdexcept>

TextButton::TextButton(int x, int y, int w, int h, std::string s, std::string srcImage) : Sprite(x, y, w, h), strText(s)
{   
    try
    {
        std::string fullSrcImage = constants::gResPath + "images/" + srcImage;
        imgTexture = IMG_LoadTexture(engine.get_ren(), fullSrcImage.c_str());
        if(imgTexture == NULL)
            throw std::runtime_error("Couldn't load image");
        
        SDL_Rect r = {};
        int result = SDL_QueryTexture(imgTexture, nullptr, nullptr, &r.w, &r.h);
        std::string error;
        if(result < 0) 
        {
             error = SDL_GetError();
             throw std::runtime_error("Couldn't query texture" + error);
        }

        setSrcRect(r.x, r.y, r.w, r.h);
        
        SDL_Surface* surface = TTF_RenderText_Solid(engine.get_font(), strText.c_str(), SDL_Color{255,255,255,255});    
        if(surface == NULL)
        {
            error = SDL_GetError();
            throw std::runtime_error("Couldn't load surface for text" + error);
        }

        textTexture = SDL_CreateTextureFromSurface(engine.get_ren(), surface);
        if(textTexture == NULL)
        {   
            error = SDL_GetError();
            throw std::runtime_error("Couldn't texture from surface" + error);
        }

        
        //setSrcRect(0, 0, surface->w, surface->h);

        SDL_FreeSurface(surface);


    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

TextButton* TextButton::getInstance(int x, int y, int w, int h, std::string s, std::string srcImage)
{
    return new TextButton(x, y, w, h, s, srcImage);
}

void TextButton::tick()
{

}

void TextButton::setText(std::string s)
{
    strText = s;
    try
    {
        std::string error;
        SDL_Surface* surface = TTF_RenderText_Solid(engine.get_font(), strText.c_str(), SDL_Color{255,255,255,255});    
        if(surface == NULL)
        {
            error = SDL_GetError();
            throw std::runtime_error("Couldn't load surface for text" + error);
        }

        textTexture = SDL_CreateTextureFromSurface(engine.get_ren(), surface);
        if(textTexture == NULL)
        {   
            error = SDL_GetError();
            throw std::runtime_error("Couldn't texture from surface" + error);
        }

        
        //setSrcRect(0, 0, surface->w, surface->h);

        SDL_FreeSurface(surface);

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

void TextButton::draw() const
{
    SDL_RenderCopy(engine.get_ren(), imgTexture, &getSrcRect(), &getDestRect());

    SDL_RenderCopy(engine.get_ren(), textTexture, &getSrcRect(), &getDestRect());
}

TextButton::~TextButton()
{
}