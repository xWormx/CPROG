#include "Level.h"

Level* Level::GetInstance(unsigned int index)
{
    return new Level(index);
}

Level::Level(unsigned int index) : levelIndex(index)
{
}

void Level::Update(System& system)
{
    UpdateSprites(system);
}

void Level::UpdateSprites(System& system)
{
    for(Sprite* s : sprites)
            s->Tick(system);

        for(Sprite* s : colliderSprites)
        {
            for(Sprite* other : colliderSprites)
            {
                if(s != other && IsColliding(s->GetColliderBounds(), other->GetColliderBounds()))
                {
                    if(s->IsTrigger())
                    {
                        s->OnTriggerEnter(other, system);
                    }
                    else
                    {
                        if(!other->IsTrigger() && !s->IsStatic())
                            system.ResolveCollision(s, other);

                        s->OnCollision(other, system);
                    }
                }
                    
            }
        }

        for(Sprite* s : added)
            sprites.push_back(s);

        added.clear();

        for(Sprite* s : removed)
        {       
            for(std::vector<Sprite*>::iterator i = sprites.begin(); i != sprites.end();)
            {
                if(*i == s)
                {
                    i = sprites.erase(i);
                }    
                else
                    i++;
            }

            for(std::vector<Sprite*>::iterator j = colliderSprites.begin(); j != colliderSprites.end();)
            {
                if(*j == s)
                    j = colliderSprites.erase(j);
                else
                    j++;
            }

            delete s;
        }

        removed.clear();
}

void Level::AddSprite(Sprite *sprite)
{
    if(sprite != nullptr)
    {
        // Se till så att inte samma pekare läggs till 2 gånger
        // vilket kan hända med textButton som tar Text* och Button* som argument.
        for(Sprite *existingSprite : sprites)
            if(sprite == existingSprite)
                return;

        added.push_back(sprite);

        if(sprite->Collider2DIsValid())
        {
            AddCollider(sprite);
        }
    }
}

void Level::AddSpriteList(std::initializer_list<Sprite*> sprites)
{
    for(Sprite* s : sprites)
        AddSprite(s);
}

void Level::RemoveSprite(Sprite* sprite)
{
    if(sprite != nullptr)
    {
        for(Sprite* existingSprite : removed)
        {
            if(sprite == existingSprite)
                return;
        }
        removed.push_back(sprite);
    }
        
}

void Level::AddCollider(Sprite *sprite)
{
    if(sprite != nullptr)
    {
        for(Sprite *existingSprite : colliderSprites)
            if(sprite == existingSprite)
                return;

        colliderSprites.push_back(sprite);
    }
    
}
const bool Level::IsColliding(const SDL_Rect& A, const SDL_Rect& B) const
{
    // y goes downwards so bottom is y + h;
    int left = A.x, right = A.x + A.w,
        top = A.y, bottom = A.y + A.h;
    
    int otherLeft = B.x, otherRight  = B.x + B.w,
        otherTop  = B.y, otherBottom = B.y + B.h;

    if(left < otherRight && right > otherLeft &&
        top < otherBottom && bottom > otherTop )
        return true;
    
    return false;
}