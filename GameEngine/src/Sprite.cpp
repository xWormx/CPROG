#include "Sprite.h"

Sprite* Sprite::getInstance(int x, int y, int w, int h, std::string srcImage)
{
    return new Sprite(x, y, w, h, srcImage);
}

void Sprite::keyDown(const SDL_Event &event)
{
    switch(getKeyCodeFromEvent(event))
    {
        case SDLK_w:
        {
            move(0.0f, -1.0f);            
        } break;
    }
    std::cout << "keyDOwn" << std::endl;
}

Sprite::Sprite(int x, int y, int w, int h, std::string srcImage) : rect{ x, y, w, h }
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

            setAreaRectToDraw(r.x, r.y, r.w, r.h);
        }

    }
}

void Sprite::draw() const
{
    SDL_RenderCopy(engine.get_ren(), texture, &getAreaToDraw(), &getRect());
}

void Sprite::move(int x, int y)
{
    rect.x += x;
    rect.y += y;
}

const SDL_Rect& Sprite::getRect() const
{
    return rect;
}

const SDL_Rect& Sprite::getAreaToDraw() const
{
    return areaToDraw;
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