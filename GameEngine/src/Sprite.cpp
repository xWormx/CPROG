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
}

void Sprite::draw() const
{
    SDL_RenderCopy(engine.get_ren(), texture, NULL, &getRect());
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

Sprite::~Sprite()
{
    
}