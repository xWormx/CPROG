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
        static Player* getInstance(int x, int y, int h, int w, std::string srcImage); 
        void tick();

        bool IsMoving()                     { return isMoving;}
        int getMoveSpeed()                  { return moveSpeed; }
        const Position& GetPosition()       { return pos; }
        const int& GetWidth()               { return width; }
        
        bool keyPressed(const int keyCode)  { return InputComponent::getKeyPressed(keyCode);}
        
        void setMoveSpeed(int speed)        { moveSpeed = speed; }
        void SetPlayerRef(Player* p)        { playerRef = p;}
        void SetUIElementRef(UIElement* tb) { txtButtonRef = tb; }
        void SetAppRef(System* app)         { appRef = app;}
        
    protected:
        Player(int x, int y, int h, int w, std::string srcImage) : MovableSprite(x,y,w,h,srcImage), pos{x, y}
        {
            width = w;
            height = h;
        }

    private:
        Position pos;
        int width;
        int height;
        int moveSpeed = 0;
        bool isMoving;
        Player* playerRef = nullptr;
        UIElement* txtButtonRef = nullptr;
        std::vector<Particle*> particles;
        //Particle* particle[50] = {};
        System* appRef;
};


#endif