#include "Sprite.h"

Sprite::Sprite(int x, int y, int w, int h, std::string srcImage) : srcRect{ x, y, w, h }
{
    std::string fullSrcPath = constants::gResPath + "images/" + srcImage;
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

void Sprite::setAreaRectToDraw(int x, int y, int w, int h)
{
    areaToDraw.x = x;
    areaToDraw.y = y;
    areaToDraw.w = w;
    areaToDraw.h = h;
}

Sprite::~Sprite()
{
    SDL_DestroyTexture(texture);
}