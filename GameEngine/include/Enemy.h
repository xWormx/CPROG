#ifndef ENEMY_H
#define ENEMY_H


#include "MovableSprite.h"
#include "Position.h"
#include "Particle.h"
#include "System.h"
#include "Player.h"
#include "Dimension.h"

class Player;

class Enemy : public MovableSprite
{
    public:
        static Enemy* GetInstance(int x, int y, int h, int w, std::string srcImage, int maxHP); 
        void Tick(System& system);

        bool IsMoving()                     { return isMoving;}
        int GetMoveSpeed()                  { return moveSpeed; }
        const Position& GetPosition()       { return pos; }
        const Dimension& GetSize()          { return size; }

        void OnCollision(Sprite* other, System& system);
        bool KeyPressed(const int keyCode)  { return InputComponent::GetKeyPressed(keyCode);}
        
        void SetMoveSpeed(int speed)        { moveSpeed = speed; }
        void SetPlayerRef(Player* p)        { playerRef = p;}
        

    protected:
        Enemy(int x, int y, int h, int w, std::string srcImage, int maxHP);


    private:
        Position pos;
        Dimension size;

        int maxHealth;
        int moveSpeed = 0;  

        unsigned int frameTick = 0;
        unsigned int particleSpawnTick = 0;
        bool isMoving;

        Player* playerRef = nullptr;
        TextButton* txtButtonRef = nullptr;
        System* appRef = nullptr;

};


#endif