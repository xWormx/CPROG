#include "Sprite.h"

// FOR IMAGES
Sprite::Sprite(int x, int y, int w, int h, std::string srcImage) : destRect{ x, y, w, h }
{
    std::string fullSrcPath = constants::gResPath + "images/" + srcImage;

    if(texture != nullptr)
        SDL_DestroyTexture(texture);
    
    texture = IMG_LoadTexture(engine.get_ren(), fullSrcPath.c_str());
    if(texture != nullptr)
    {
        SDL_Rect r;
        int result = SDL_QueryTexture(texture, nullptr, nullptr, &r.w, &r.h);
        if(result != 0)
        {
            std::cout << "couldn't query texture" << std::endl;
        }
        else
        {
            r.x = 0;
            r.y = 0;                

            setSrcRect(r.x, r.y, r.w, r.h);
        }
    }
}
const void Sprite::DEBUGDrawLineFrame() const
{
    SDL_Point points[5] = {{destRect.x, destRect.y}, 
                            {destRect.x, destRect.y + destRect.h},
                            {destRect.x + destRect.w, destRect.y + destRect.h},
                            {destRect.x + destRect.w, destRect.y},
                            {destRect.x, destRect.y}};
    SDL_RenderDrawLines(engine.get_ren(), points, sizeof(points)/sizeof(SDL_Point));
}

const bool Sprite::DEBUGDidCollide(const Sprite& other) const
{
    // y goes downwards so bottom is y + h;
    int left = destRect.x, right = destRect.x + destRect.w,
        top = destRect.y, bottom = destRect.y + destRect.h;
    
    int otherLeft = other.destRect.x, otherRight  = other.destRect.x + other.destRect.w,
        otherTop  = other.destRect.y, otherBottom = other.destRect.y + other.destRect.h;

    if(left < otherRight && right > otherLeft &&
        top < otherBottom && bottom > otherTop )
        return true;
    
    return false;
}

// FOR TEXT
Sprite::Sprite(int x, int y, int w, int h) : destRect{x,y,w,h}
{
}

const SDL_Rect& Sprite::getSrcRect() const
{
    return srcRect;
}

const SDL_Rect& Sprite::getDestRect() const
{
    return destRect;
}

const SDL_Texture* Sprite::getTexture() const
{
    return texture;
}

void Sprite::setSrcRect(int x, int y, int w, int h)
{
    srcRect.x = x;
    srcRect.y = y;
    srcRect.w = w;
    srcRect.h = h;
}

void Sprite::setDestRect(int x, int y, int w, int h)
{
    destRect.x = x;
    destRect.y = y;
    destRect.w = w;
    destRect.h = h;
}

Sprite::~Sprite()
{
    SDL_DestroyTexture(texture);
}