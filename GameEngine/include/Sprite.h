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
class Sprite
{
    public:
        virtual void Draw() const = 0; 
        virtual void Tick(System& system) = 0;
     
        const bool CompareTag(const std::string& otherSpriteTag) const;

        const int& GetDx() const {return dx;}
        const int& GetDy() const {return dy;}
        const SDL_Rect& GetSrcRect() const;
        const SDL_Rect& GetDestRect() const;
        const SDL_Texture* getTexture() const;
        const SDL_Rect& GetColliderBounds() {return collider->GetBounds();}
        const bool Collider2DIsValid() { return collider != nullptr; }

        

        void SetTag(std::string tagName);
        void InstallCollider2D(const bool& colliderState, const SDL_Rect& bounds, const bool& _isTrigger, const bool& _isStatic);
        void SetColliderActive(const bool& state); 
        void SetColliderBounds(const SDL_Rect& bounds);
    
        const bool& IsTrigger() const { return collider->IsTrigger(); }
        const bool& IsStatic() const { return collider->IsStatic(); }
        virtual void OnCollision(Sprite* other, System& system){}
        virtual void OnTriggerEnter(Sprite* other, System& system){}

        const void DEBUGDrawSpriteBounds() const;
        const void DEBUGDrawColliderBounds() const;
        const bool DEBUGDidCollide(const Sprite& other) const;
        virtual ~Sprite();

        friend class MovableSprite;
        friend class TextButton;
        friend class TextFragment;
        friend class TextField;
        friend class Button;
        friend class Particle;
        friend class System;
    protected:
        Sprite(int x, int y, int w, int h, std::string srcImage);
        Sprite(int x, int y, int w, int h);
    private:
        int dx = 0, dy = 0;
        std::string spriteTag;

        SDL_Rect srcRect; // What part to draw
        SDL_Rect destRect; // Where to draw it
        SDL_Texture* texture = nullptr;     

        Collider2D *collider = nullptr;

        void setDestRect(int x, int y, int w, int h);
        void setSrcRect(int x, int y, int w, int h);
        void SetAlpha(Uint8 alpha) const;
        void SetMovementDirection(int dX, int dY);
        Sprite(const Sprite&) = delete;
        const Sprite& operator=(const Sprite&) = delete;      

        bool isColliding = false;       
};


#endif