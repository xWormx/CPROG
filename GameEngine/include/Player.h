#ifndef PLAYER_H
#define PLAYER_H


#include "System.h"
#include "MovableSprite.h"
#include "Position.h"
#include "TextButton.h"
#include "Particle.h"
#include "HPSlot.h"
#include "Enemy.h"

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
        
        void OnCollision(Sprite* other);
        bool keyPressed(const int keyCode)  { return InputComponent::getKeyPressed(keyCode);}
        
        void setMoveSpeed(int speed)        { moveSpeed = speed; }
        void SetTextButtonRef(TextButton* tb) { txtButtonRef = tb; }
        

        
    protected:
        Player(int x, int y, int h, int w, std::string srcImage, int maxHP);


    private:
        Position pos;
        Dimension size;
        int maxHealth;
        int width;
        int height;
        int moveSpeed = 0;   

        // Animation
        unsigned int animationFrame = 0;
        unsigned int animationFrameTick = 0;
        unsigned int particleSpawnTick = 0;
        
        bool isMoving;
        
        Player* playerRef = nullptr;
        TextButton* txtButtonRef = nullptr;
        std::vector<Particle*> particles;

        bool healthInitialized;
        std::vector<HPSlot*> healthBar;

};


#endif