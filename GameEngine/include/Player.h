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
        static Player* GetInstance(int x, int y, int h, int w, std::string srcImage, int maxHP); 
        void Tick(System& system);

        bool IsMoving()                     { return isMoving;}
        int GetMoveSpeed()                  { return moveSpeed; }
        const Position& GetPosition()       { return pos; }
        const Dimension& GetSize()          { return size; }

        void OnCollision(Sprite* other, System& system);
        
        void SetMoveSpeed(int speed)        { moveSpeed = speed; }
        void SetTextButtonRef(TextButton* tb) { txtButtonRef = tb; }

        void TakeDamage(int damage);
        void UpdateHealth(System& system);

        
    protected:
        Player(int x, int y, int h, int w, std::string srcImage, int maxHP);


    private:
        Position pos;
        Dimension size;
        int maxHealth;
        int moveSpeed = 0; 
        int dx, dy;  

        // Animation
        unsigned int animationFrame = 0;
        unsigned int animationFrameTick = 0;
        unsigned int particleSpawnTick = 0;
        
        bool isMoving;
        
        TextButton* txtButtonRef = nullptr;

        bool healthInitialized;
        int currentHealth;
        int damageTaken;
        std::vector<HPSlot*> healthBar;

};


#endif