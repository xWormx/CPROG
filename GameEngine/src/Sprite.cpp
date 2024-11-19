#include "Sprite.h"

// FOR IMAGES
Sprite::Sprite(int x, int y, int w, int h, std::string srcImage) : destRect{ x, y, w, h }
{
    std::string fullSrcPath = constants::gResPath + "images/" + srcImage;

    if(texture != nullptr)
        SDL_DestroyTexture(texture);
    
    texture = IMG_LoadTexture(engine.Get_ren(), fullSrcPath.c_str());
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
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    }
}

// FOR TEXTFRAGMENT
Sprite::Sprite(int x, int y, int w, int h) : destRect{x,y,w,h}
{

}

const void Sprite::DEBUGDrawSpriteBounds() const
{
    SDL_SetRenderDrawColor(engine.Get_ren(), 0x00, 0xbb, 0xff, 0xff);

    SDL_Point points[5] = {{destRect.x, destRect.y}, 
                            {destRect.x, destRect.y + destRect.h},
                            {destRect.x + destRect.w, destRect.y + destRect.h},
                            {destRect.x + destRect.w, destRect.y},
                            {destRect.x, destRect.y}};
    
    SDL_RenderDrawLines(engine.Get_ren(), points, sizeof(points)/sizeof(SDL_Point));
}

const void Sprite::DEBUGDrawColliderBounds() const
{
    SDL_RenderDrawRect(engine.Get_ren(), &collider.GetBounds());
}

const bool Sprite::DEBUGDidCollide(const Sprite& other) const
{
    // y goes downwards so bottom is y + h;
    int left = collider.GetBounds().x, right = collider.GetBounds().x + collider.GetBounds().w,
        top = collider.GetBounds().y, bottom = collider.GetBounds().y + collider.GetBounds().h;
    
    int otherLeft = other.collider.GetBounds().x, otherRight  = other.collider.GetBounds().x + other.collider.GetBounds().w,
        otherTop  = other.collider.GetBounds().y, otherBottom = other.collider.GetBounds().y + other.collider.GetBounds().h;

    if(left < otherRight && right > otherLeft &&
        top < otherBottom && bottom > otherTop )
        return true;
    
    return false;
}

const bool Sprite::CompareTag(const std::string& otherSpriteTag) const
{
    return spriteTag == otherSpriteTag;
}

const SDL_Rect& Sprite::GetSrcRect() const
{
    return srcRect;
}

const SDL_Rect& Sprite::GetDestRect() const
{
    return destRect;
}

const SDL_Texture* Sprite::getTexture() const
{
    return texture;
}

Sprite::~Sprite()
{
    if(texture != nullptr)
        SDL_DestroyTexture(texture);
}

void Sprite::SetTag(std::string tagName)
{
    spriteTag = tagName;
}

void Sprite::SetCollider(const bool& colliderState, SDL_Rect bounds)
{
    CanCollide(colliderState);
    SetColliderBounds(bounds);
}

void Sprite::SetAlpha(Uint8 alpha) const
{
    SDL_SetTextureAlphaMod(texture, alpha);
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
