#include "TextButton.h"
#include <stdexcept>

TextButton* TextButton::getInstance(int x, int y, int w, int h, std::string s, std::string srcImage)
{
    return new TextButton(x, y, w, h, s, srcImage);
}

TextButton::TextButton(int x, int y, int w, int h, std::string s, std::string srcImage) : Sprite(x, y, w, h), strText(s), textDestRect{x+15,y+5,w-20,h-5}
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

        if(textTexture != nullptr)
            SDL_DestroyTexture(textTexture);
        
        textTexture = SDL_CreateTextureFromSurface(engine.get_ren(), surface);
        if(textTexture == NULL)
        {   
            error = SDL_GetError();
            throw std::runtime_error("Couldn't texture from surface" + error);
        }

        result = SDL_QueryTexture(textTexture, nullptr, nullptr, &r.w, &r.h);
        if(result < 0) 
        {
             error = SDL_GetError();
             throw std::runtime_error("Couldn't query texture" + error);
        }
        textSrcRect.x = 0;
        textSrcRect.y = 0;
        textSrcRect.w = r.w;
        textSrcRect.h = r.h;

        SDL_FreeSurface(surface);


    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
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

        if(textTexture != nullptr)
            SDL_DestroyTexture(textTexture);

        textTexture = SDL_CreateTextureFromSurface(engine.get_ren(), surface);
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
        textSrcRect.x = 0;
        textSrcRect.y = 0;
        textSrcRect.w = r.w;
        textSrcRect.h = r.h;
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

    SDL_RenderCopy(engine.get_ren(), textTexture, &textSrcRect, &textDestRect);
}

void TextButton::SetPosition(int x, int y)
{

    setDestRect(x, y, getDestRect().w, getDestRect().h);
    textDestRect.x = x+8;
    textDestRect.y = y+2;
}

TextButton::~TextButton()
{
}