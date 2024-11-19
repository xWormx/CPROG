#ifndef SPRITE_H
#define SPRITE_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_Image.h"
#include <string>
#include "Constants.h"

#include "GameEngine.h"
#include "InputComponent.h"
#include "System.h"
#include "Collider2D.h"

class System;
class Sprite : public InputComponent
{
    public:
        virtual void draw() const = 0; 
        virtual void Tick(System& system) = 0;
     
        const bool CompareTag(const std::string& otherSpriteTag) const;

        const SDL_Rect& getSrcRect() const;
        const SDL_Rect& getDestRect() const;
        const SDL_Texture* getTexture() const;
        const SDL_Rect& GetColliderBounds() {return collider.GetBounds();}

        void SetTag(std::string tagName);
        void SetCollider(const bool& colliderState, SDL_Rect bounds);
        void SetColliderBounds(const SDL_Rect& bounds){collider.SetBounds(bounds);}
        void CanCollide(const bool& colliderState) { collider.SetCollideState(colliderState); }
        virtual void OnCollision(Sprite* other, System& system){}

        const void DEBUGDrawSpriteBounds() const;
        const void DEBUGDrawColliderBounds() const;
        const bool DEBUGDidCollide(const Sprite& other) const;
        virtual ~Sprite();

        friend class MovableSprite;
        friend class TextButton;
        friend class TextFragment;
        friend class Button;
        friend class Particle;
    protected:
        Sprite(int x, int y, int w, int h, std::string srcImage);
        Sprite(int x, int y, int w, int h);
    private:
        std::string spriteTag;

        SDL_Rect srcRect; // What part to draw
        SDL_Rect destRect; // Where to draw it
        SDL_Texture* texture = nullptr;     

        Collider2D collider;

        void setDestRect(int x, int y, int w, int h);
        void setSrcRect(int x, int y, int w, int h);
        void SetAlpha(Uint8 alpha) const;

        Sprite(const Sprite&) = delete;
        const Sprite& operator=(const Sprite&) = delete;      

        bool isColliding = false;
        
};


#endif