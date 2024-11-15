#ifndef PLAYER_H
#define PLAYER_H


#include "MovableSprite.h"
#include "Position.h"
#include "UIElement.h"
#include "Particle.h"
#include "System.h"


class Player : public MovableSprite
{
    public:
        static Player* getInstance(int x, int y, int h, int w, std::string srcImage, int maxHP); 
        void tick(System& system);

        bool IsMoving()                     { return isMoving;}
        int getMoveSpeed()                  { return moveSpeed; }
        const Position& GetPosition()       { return pos; }
        const int& GetWidth()               { return width; }
        const int& GetHeight()               { return height; }

        const bool CheckCollision(Sprite* other) const;
        bool keyPressed(const int keyCode)  { return InputComponent::getKeyPressed(keyCode);}
        
        void setMoveSpeed(int speed)        { moveSpeed = speed; }
        void SetPlayerRef(Player* p)        { playerRef = p;}
        void SetUIElementRef(UIElement* tb) { txtButtonRef = tb; }
        void SetAppRef(System* app)         { appRef = app;}
        void SetSpriteCollection(const std::vector<Sprite*>& collection) { spriteCollection = &collection; }
        
    protected:
        Player(int x, int y, int h, int w, std::string srcImage, int maxHP);


    private:
        Position pos;
        int maxHealth;
        int width;
        int height;
        int moveSpeed = 0;   
        unsigned int frameTick = 0;
        unsigned int particleSpawnTick = 0;
        bool isMoving;
        Player* playerRef = nullptr;
        UIElement* txtButtonRef = nullptr;
        System* appRef = nullptr;
        std::vector<Particle*> particles;
        const std::vector<Sprite*> *spriteCollection = nullptr;
        //Particle* particle[50] = {};

};


#endif