#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <initializer_list>
#include "Sprite.h"
#include "System.h"

class Sprite;
class System;
class Level
{
    public:
        static Level* GetInstance(unsigned int index, std::initializer_list<Sprite*> sprites); 
        const unsigned int& GetLevelIndex() const { return levelIndex; }
        void Update(System& system);

        void AddSprite(Sprite* sprite);
        void RemoveSprite(Sprite* sprite);
        

        
        std::vector<Sprite*> GetSprites() { return sprites;}        
        std::vector<Sprite*> GetAdded() { return added;}
        std::vector<Sprite*> GetRemoved() { return removed;}
        std::vector<Sprite*> GetColliders() { return colliderSprites;}


    protected:
        Level(unsigned int index, std::initializer_list<Sprite*> sprites);

    private:
        unsigned int levelIndex;
        std::vector<Sprite*> sprites;
        std::vector<Sprite*> added;
        std::vector<Sprite*> removed;
        std::vector<Sprite*> colliderSprites;
        std::vector<Level*> levels;

        void UpdateSprites(System& system);
        void AddCollider(Sprite* sprite);
        const bool IsColliding(const SDL_Rect& A, const SDL_Rect& B) const;
};


#endif